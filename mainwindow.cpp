#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Animal.h"
#include "config/config.h"
#include <cmath>
#include <sstream>

#include <QDockWidget>
#include <QKeyEvent>
#include <QFileDialog>

#include "Vegetal.h"
#include "Water.h"
#include "Meat.h"
#include "Carnivore.h"
#include "Herbivore.h"
#include "SaveManager.h"

#include <QFile>

//DEBUG
#include <iostream>
#include <cstdlib>
#include <ctime>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //set central widget
    loadWorld();
    worldWidget.setWorld(&world);
    setCentralWidget(&worldWidget);
    worldWidget.updateScene();
    //set dock widget
    QDockWidget * dockWidget = new QDockWidget(tr("Entity View"),this);
    dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dockWidget->setWidget(&entityWidget);
    addDockWidget(Qt::RightDockWidgetArea, dockWidget);
    //entityWidget.updateView();
    entityWidget.update();
    //(re)set menu bar
    this->menuBar()->clear();
    fileMenu = this->menuBar()->addMenu(tr("File"));
    simulationMenu = this->menuBar()->addMenu(tr("Simulation"));
    animalMenu = this->menuBar()->addMenu(tr("Animal"));
    fileExitAction = fileMenu->addAction(tr("Exit"));
    saveWorldAction = fileMenu->addAction(tr("Save world as..."));
    loadWorldAction = fileMenu->addAction(tr("Load world"));
    simmulationStartStopAction = simulationMenu->addAction(tr("Start simulation"));
    saveNeuralNetworkAction = animalMenu->addAction(tr("Save neural network as..."));
    loadNeuralNetworkAction = animalMenu->addAction(tr("Load neural network"));
    animalMenu->setEnabled(false);

    //event managment
    QObject::connect(&worldWidget,SIGNAL(animalSelected(std::weak_ptr<Animal>)),&entityWidget,SLOT(setAnimal(std::weak_ptr<Animal>)));
    QObject::connect(&worldWidget,SIGNAL(animalSelected(std::weak_ptr<Animal>)),this,SLOT(setSelectedAnimal(std::weak_ptr<Animal>)) );
    QObject::connect(fileExitAction,SIGNAL(triggered(bool)),this,SLOT(close()));
    QObject::connect(simulationMenu,SIGNAL(triggered(QAction*)),this,SLOT(switchTimer()));
    QObject::connect(&worldWidget,SIGNAL(sceneUpdated()),&entityWidget,SLOT(update()));
    QObject::connect(&worldWidget,SIGNAL(sceneUpdated()),this,SLOT(updateStatusBar()));
    QObject::connect(saveNeuralNetworkAction,SIGNAL(triggered(bool)),this,SLOT(saveNeuralNetwork()));
    QObject::connect(loadNeuralNetworkAction, SIGNAL(triggered(bool)),this, SLOT(loadNeuralNetwork()));
    QObject::connect(saveWorldAction, SIGNAL(triggered(bool)),this, SLOT(saveWorld()));
    QObject::connect(loadWorldAction, SIGNAL(triggered(bool)),this, SLOT(loadWorldSave()));
}

void MainWindow::loadWorld()
{
    const QString worldSave("../save/world.xml");
    loadXML(worldSave);

  /*  Animal * animal0 = new Animal(130,278,10,50,&world);
    Animal * animal1 = new Animal(160,278,10,50,&world);
    world.addEntity(animal0);
    world.addEntity(animal1);
    Animal * animal2 = new Animal(99,319,10,50,&world);
    Animal * animal3 = new Animal(40,99,10,50,&world);
    Animal * animal4 = new Animal(199,236,10,50,&world);
    Animal * animal5 = new Animal(215,025,10,50,&world);
    Animal * animal6 = new Animal(125,350,10,50,&world);
    Animal * animal7 = new Animal(350,50,10,50,&world);

    world.addEntity(animal2);
    world.addEntity(animal3);
    world.addEntity(animal4);
    world.addEntity(animal5);
    world.addEntity(animal6);
    world.addEntity(animal7);*/

    //random generator
//
    srand(std::time(0));
    //world.feedWithRandomAnimal(40);
    //world.feedWithRandomHerbivore(20);
    //world.feedWithRandomCarnivore(7);

    /*shared_ptr<Animal> male(make_shared<Animal>(100, 250, 10, 50, 2, &world, false) );
    shared_ptr<Animal> female(make_shared<Animal>(300, 250, 10, 50, 2, &world, true) );
    female->turn(PI);

    world.addEntity(male);
    world.addEntity(female);*/

/*Animal * animal = new Animal(1.46671, 491.343,10,50,&world);
animal->turn(3.17);
world.addEntity(animal);*/
    /*Animal * animal0 = new Animal(400,450,10,50,&world);
    Animal * animal1 = new Animal(180,60,10,50,&world);
    Animal * animal2 = new Animal(350,120,10,50,&world);
    animal0->turn(PI/2);
    animal2->turn(PI);

    world.addEntity(animal0);
    world.addEntity(animal1);
    world.addEntity(animal2);
    Animal * animal3 = new Animal(100,200,10,50,&world);
    Animal * animal4 = new Animal(200,200,10,50,&world);
    animal4->turn(PI);

//    world.addEntity(animal3);
//    world.addEntity(animal4);

    world.addEntity(animal3);
    world.addEntity(animal4);*/

}

void MainWindow::loadXML(QString worldSave)
{
   QFile* xmlFile = new QFile(worldSave);
   if(!xmlFile->exists())
   {
     std::cout << "file does not exist" << std::endl;
   }

   if(!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text))
   { //error
     std::cout << "Can't open the file" << std::endl;
   }
   QXmlStreamReader reader(xmlFile);

   while(!reader.atEnd() && !reader.hasError())
   {
     QXmlStreamReader::TokenType token = reader.readNext();
     if(token == QXmlStreamReader::StartDocument)
     { continue;
     }

     if(token == QXmlStreamReader::StartElement)
     {
      if(reader.name() == "World")
      {
         this->parseWorld(reader);
      }
     }
   }
   if(reader.hasError())
   { std::cout << "Error in reading XML in constructor" << std::endl;
   }
   delete xmlFile;
}

void MainWindow::parseWorld(QXmlStreamReader& reader)
{
  int xWorld, yWorld;
  unsigned ageWorld;

  if(reader.tokenType() != QXmlStreamReader::StartElement &&
     reader.name() != "World")
  { // error
    std::cout << "Error in reading Wolrd" << std::endl;
  }
  reader.readNext();
  while(!(reader.tokenType() == QXmlStreamReader::EndElement &&
         reader.name() == "World"))
  {
    if(reader.tokenType() == QXmlStreamReader::StartElement)
    {
      if(reader.name() == "Entity")
      {
        this->parseEntity(reader);
      }
      else if(reader.name() == "x")
      {
        xWorld = reader.readElementText().toInt();
      }
      else if(reader.name() == "y")
      {
        yWorld = reader.readElementText().toInt();
      }
      else if(reader.name() == "age")
      {
        ageWorld = reader.readElementText().toUInt();
      }
      else
      { //error
        std::cout << "Unknown Token" << std::endl;
      }
    }
    reader.readNext();
  }
  world.setSize(xWorld,yWorld);
  world.setWorldAge(ageWorld);
}

void MainWindow::parseEntity(QXmlStreamReader& reader)
{
  QString type;
  double xEntity=0.0, yEntity=0.0, radiusEntity=INITIAL_RADIUS;
  double angle = 0.0;
  int maxSpeed = MAX_SPEED;
  double attack = -2;
  double energy = DEFAULT_ENERGY;
  bool sex = true;
  NeuralNetwork * nn = nullptr;
  int mating = 0;
  int age = 0;
  int quantity = 0, maxQuantity = 0;
  int hunger = 0;
  int thirst = 0;
  int health = MAX_HEALTH;

  if(!reader.tokenType() == QXmlStreamReader::StartElement &&
      reader.name() == "Entity")
  { //error
  }

  QXmlStreamAttributes attributes = reader.attributes();
  if(attributes.hasAttribute("type"))
  {
    type = attributes.value("type").toString();
  }
  else
  { //error
    std::cout << "No Attribute type" << std::endl;
  }

  reader.readNext();
  while(!(reader.tokenType() == QXmlStreamReader::EndElement &&
         reader.name() == "Entity"))
  {
    if(reader.tokenType() == QXmlStreamReader::StartElement)
    {
      if(reader.name() == "x")
      {
          xEntity = reader.readElementText().toDouble();
      }
      else if(reader.name() == "y")
      {
          yEntity = reader.readElementText().toDouble();
      }
      else if(reader.name() == "radius")
      {
          radiusEntity = reader.readElementText().toDouble();
      }
      else if(reader.name() == "angle")
      {
          angle = reader.readElementText().toDouble();
      }
      else if(reader.name() == "attack")
      {
          attack = reader.readElementText().toDouble();
      }
      else if(reader.name() == "energy")
      {
          energy = reader.readElementText().toDouble();
      }
      else if(reader.name() == "sex")
      {
          sex = (reader.readElementText().toLower()=="true");
      }
      else if(reader.name() == "maxSpeed")
      {
          maxSpeed = reader.readElementText().toInt();
      }
      else if(reader.name() == "NeuralNetwork")
      {
          SaveManager savManager;
          nn = savManager.LoadNetwork(reader);
      }
      else if(reader.name() == "mating")
      {
          mating = reader.readElementText().toInt();
      }
      else if(reader.name() == "age")
      {
          age = reader.readElementText().toInt();
      }
      else if(reader.name() == "quantity")
      {
          quantity = reader.readElementText().toInt();
      }
      else if(reader.name() == "maxQuantity")
      {
          maxQuantity = reader.readElementText().toInt();
      }
      else if(reader.name() == "hunger")
      {
          hunger = reader.readElementText().toInt();
      }
      else if(reader.name() == "thirst")
      {
          thirst = reader.readElementText().toInt();
      }
      else if(reader.name() == "health")
      {
          health = reader.readElementText().toInt();
      }
      else
      { //error
      }
    }
    reader.readNext();
  }

  if(type == "Vegetal")
  {
    if(maxQuantity==0)
        maxQuantity=VEGETAL_MAXQUANTITY;
    if(quantity==0)
        quantity=maxQuantity;
    shared_ptr<Vegetal> entity( make_shared<Vegetal>(xEntity, yEntity, radiusEntity, maxQuantity));
    entity->setCurrantQuantity(quantity);
    world.addEntity(entity);
  }
  else if(type == "Water")
  {
      if(maxQuantity==0)
          maxQuantity=WATER_MAXQUANTITY;
      if(quantity==0)
          quantity=maxQuantity;
    shared_ptr<Water> entity( make_shared<Water>(xEntity, yEntity, radiusEntity, maxQuantity));
    entity->setCurrantQuantity(quantity);
    world.addEntity(entity);
  }
  else if(type == "Meat")
  {
    shared_ptr<Meat> entity( make_shared<Meat>(xEntity, yEntity, radiusEntity, maxQuantity));
    entity->setCurrantQuantity(quantity);
    world.addEntity(entity);
  }
  else if(type == "Herbivore")
  {
      if(nn == nullptr)
      {
          vector<unsigned int> layerSizes;
          for(unsigned int i = 0; i < NB_LAYERS; i++)
          {
            layerSizes.push_back(LAYER_SIZES[i]);
          }
          nn = new NeuralNetwork(layerSizes);
      }
      if(attack==-2)
          attack = ATTACK_HERBIVORE;
      shared_ptr<Herbivore> entity( make_shared<Herbivore>(xEntity, yEntity, radiusEntity,maxSpeed, attack, energy, &world, nn, mating));
      entity->setSex(sex);
      entity->setAge(age);
      entity->setAngle(angle);
      entity->setHunger(hunger);
      entity->setThirst(thirst);
      entity->setHealth(health);
      world.addEntity(entity);
  }
  else if(type == "Carnivore")
  {
      if(nn == nullptr)
      {
          vector<unsigned int> layerSizes;
          for(unsigned int i = 0; i < NB_LAYERS; i++)
          {
            layerSizes.push_back(LAYER_SIZES[i]);
          }
          nn = new NeuralNetwork(layerSizes);
      }
      if(attack==-2)
          attack = ATTACK_CARNIVORE;
      shared_ptr<Carnivore> entity( make_shared<Carnivore>(xEntity, yEntity, radiusEntity,maxSpeed, attack, energy, &world, nn, mating));
      entity->setSex(sex);
      entity->setAge(age);
      entity->setAngle(angle);
      entity->setHunger(hunger);
      entity->setThirst(thirst);
      entity->setHealth(health);
      world.addEntity(entity);
  }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::switchTimer()
{
    if(worldWidget.isSimulationRunning())
    {
        worldWidget.suspendSimulation();
        simmulationStartStopAction->setText(tr("Restart simulation"));
    }
    else
    {
        worldWidget.startSimulation();
        simmulationStartStopAction->setText(tr("Stop simulation"));
    }
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Space)
    {
        switchTimer();
    }
    else if(e->key()==Qt::Key_Enter || e->key()==Qt::Key_Return)
    {
        if(!worldWidget.isSimulationRunning())
        {
            worldWidget.tick();
        }
    }
}

void MainWindow::setSelectedAnimal(std::weak_ptr<Animal> a)
{
    selectedAnimal = a;
    //enable or disable the animal menu
    if(a.use_count()!=0)
    {
        animalMenu->setEnabled(true);
    }
    else
    {
        animalMenu->setEnabled(false);
    }
}

void MainWindow::updateStatusBar()
{
    QString message = tr("number of living: %1 Age of the World: %2 ticks").arg(world.getNumberOfLiving()).arg(world.getWorldAge());
    this->statusBar()->showMessage(message);
}

void MainWindow::saveNeuralNetwork()
{
    if(shared_ptr<Animal> a = selectedAnimal.lock())
        saveNeuralNetwork(a,true);
}

void MainWindow::saveNeuralNetwork(shared_ptr<Animal> a, bool pauseDuringSave)
{
    bool pause = false;
    if(pauseDuringSave && worldWidget.isSimulationRunning())
        pause = true;
    if(pause)
        worldWidget.suspendSimulation();
    NeuralNetwork nn = *(a->getBrain()); //copy the neural network
    SaveManager saveManager;
    /*QFileDialog fileDialog(this,tr("Save animal Neurale Network"));
    fileDialog.setDefaultSuffix("xml");*/
    QString filter = "XML files (*.xml);;All files (*.*)";
    QString defaultFilter = "XML files (*.xml)";
    QString filePath = QFileDialog::getSaveFileName(this,tr("Save animal Neurale Network"),QDir::currentPath(),
                                                    filter,&defaultFilter);
    saveManager.SaveNetwork(nn,filePath);
    if(pause)
        worldWidget.startSimulation();
}

void MainWindow::loadNeuralNetwork()
{
    if(shared_ptr<Animal> a = selectedAnimal.lock())
        loadNeuralNetwork(a,true);
}

void MainWindow::loadNeuralNetwork(shared_ptr<Animal> a, bool pauseDuringLoad)
{
    bool pause = false;
    if(pauseDuringLoad && worldWidget.isSimulationRunning())
        pause = true;
    if(pause)
        worldWidget.suspendSimulation();

    QString filter = "XML files (*.xml);;All files (*.*)";
    QString defaultFilter = "XML files (*.xml)";
    QString filePath = QFileDialog::getOpenFileName(this,tr("Load animal Neural Network"),QDir::currentPath(),
                                                    filter,&defaultFilter);
    SaveManager saveManager;
    NeuralNetwork* newBrain = saveManager.LoadNetwork(filePath);
    a->setBrain(newBrain);
    if(pause)
        worldWidget.startSimulation();
}

void MainWindow::saveWorld(bool pauseDuringSave)
{
    bool pause = false;
    if(pauseDuringSave && worldWidget.isSimulationRunning())
        pause = true;
    if(pause)
        worldWidget.suspendSimulation();

    SaveManager saveManager;
    QString filter = "XML files (*.xml);;All files (*.*)";
    QString defaultFilter = "XML files (*.xml)";
    QString filePath = QFileDialog::getSaveFileName(this,tr("Save animal Neurale Network"),QDir::currentPath(),
                                                    filter,&defaultFilter);
    saveManager.saveWorld(world,filePath);

    if(pause)
            worldWidget.startSimulation();
}

void MainWindow::loadWorldSave(bool pauseDuringLoad)
{
    bool pause = false;
    if(pauseDuringLoad && worldWidget.isSimulationRunning())
        pause = true;
    if(pause)
        worldWidget.suspendSimulation();

    QString filter = "XML files (*.xml);;All files (*.*)";
    QString defaultFilter = "XML files (*.xml)";
    QString filePath = QFileDialog::getOpenFileName(this,tr("Load animal Neural Network"),QDir::currentPath(),
                                                    filter,&defaultFilter);
    world = World();
    loadXML(filePath);
    worldWidget.setWorld(&world);

    if(pause)
        worldWidget.startSimulation();
}
