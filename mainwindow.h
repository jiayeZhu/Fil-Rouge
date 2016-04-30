#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include <QXmlStreamReader>

#include "WorldWidget.h"
//#include "EntityViewWidget.h"
#include "EntityFrame.h"
#include "World.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void switchTimer();
    void keyPressEvent(QKeyEvent * e);
    void saveNeuralNetwork(std::shared_ptr<Animal> a, bool pauseDuringSave);
    void saveNeuralNetwork();
    void loadNeuralNetwork(std::shared_ptr<Animal> a, bool pauseDuringLoad);
    void loadNeuralNetwork();
    void setSelectedAnimal(std::weak_ptr<Animal> a);
    void updateStatusBar();

private:
    void loadWorld();
    void loadXML(QString worldSave);
    void parseWorld(QXmlStreamReader& reader);
    void parseEntity(QXmlStreamReader& reader);


private:
    //ui
    Ui::MainWindow *ui;
    WorldWidget worldWidget;
    //EntityViewWidget entityWidget;
    EntityFrame entityWidget;
    QMenu * fileMenu;
    QMenu * simulationMenu;
    QMenu * animalMenu;
    QAction * simmulationStartStopAction;
    QAction * fileExitAction;
    QAction * saveNeuralNetworkAction;
    QAction * loadNeuralNetworkAction;

    World world;
    std::weak_ptr<Animal> selectedAnimal;
};

#endif // MAINWINDOW_H
