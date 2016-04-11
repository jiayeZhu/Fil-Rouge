#include "WorldColors.h"

#include <typeinfo>
#include "Animal.h"
#include "Herbivore.h"
#include "Carnivore.h"
#include "Vegetal.h"
#include "Water.h"
#include "Meat.h"

WorldColors::WorldColors()
{
    backgroundBrush = QBrush(QColor(255,255,255));
    backgroundPen = QPen();
    waterBrush = QBrush(Qt::blue);
    waterPen = QPen(Qt::blue);
    grassBrush = QBrush(Qt::green);
    grassPen = QPen(Qt::green);
    meatBrush = QBrush(QColor(212,60,0));
    meatPen = QPen(QColor(212,60,0));

    teamsPen = QPen(Qt::black);
    teamsSelectedPen = QPen(Qt::yellow);
    teamsEye = QBrush(Qt::black);
    teamsBrushs.push_back(QBrush(Qt::darkGreen));
    teamsBrushs.push_back(QBrush(Qt::red));
    teamsBrushs.push_back(QBrush(Qt::cyan));
    teamsBrushs.push_back(QBrush(Qt::yellow));
    teamsNullBrush = QBrush(Qt::gray);
    teamsNullPen = QPen(Qt::gray);
}

QBrush & WorldColors::getEntityBrush(const shared_ptr<Entity> entity)
{
    //TODO: complete with the corecte class name (don't existe when I wrote this)
    if(entity == nullptr)
    {
        return teamsNullBrush;
    }
    else if(typeid(*entity) == typeid( Animal ))
    {
        return teamsBrushs.at(2);
    }
    else if(typeid(*entity) == typeid( Herbivore ))
    {
        return teamsBrushs.at(0);
    }
    else if(typeid(*entity) == typeid( Carnivore ))
    {
        return teamsBrushs.at(1);
    }
    else if(typeid(*entity) == typeid( Vegetal ))
    {
      return grassBrush;
    }
    else if(typeid(*entity) == typeid( Water))
    {
      return waterBrush;
    }
    else if(typeid(*entity) == typeid( Meat))
    {
      return meatBrush;
    }
    /*
    else if(typeid(entity) == typeid( ... ))
    {
    }
    [...]
    */
    return backgroundBrush;
}

QPen & WorldColors::getEntityPen(const shared_ptr<Entity> entity)
{
    //TODO: complete with the corecte class name (don't existe when I wrote this)
    if(entity == nullptr)
    {
        return teamsNullPen;
    }
    else if(typeid(*entity) == typeid( Animal ))
    {
        return teamsPen;
    }
    else if(typeid(*entity) == typeid( Herbivore ))
    {
        return teamsPen;
    }
    else if(typeid(*entity) == typeid( Carnivore ))
    {
        return teamsPen;
    }
    else if(typeid(*entity) == typeid( Vegetal ))
    {
      return grassPen;
    }
    else if(typeid(*entity) == typeid( Water ))
    {
      return waterPen;
    }
    else if(typeid(*entity) == typeid( Meat ))
    {
      return meatPen;
    }
    /*
    else if(typeid(entity) == typeid( ... ))
    {
    }
    [...]
    */
    return backgroundPen;
}

QBrush & WorldColors::getWaterBrush()
{
    return waterBrush;
}

QPen & WorldColors::getWaterPen()
{
    return waterPen;
}

QBrush & WorldColors::getGrassBrush()
{
    return grassBrush;
}

QPen & WorldColors::getGrassPen()
{
    return grassPen;
}

std::vector<QBrush> & WorldColors::getTeamsBrushs()
{
    return teamsBrushs;
}

QPen & WorldColors::getTeamsPen()
{
    return teamsPen;
}

QBrush & WorldColors::getBackgroundBrush()
{
    return backgroundBrush;
}

QBrush & WorldColors::getTeamsEyeBrush()
{
    return teamsEye;
}

QPen & WorldColors::getTeamsSelectedPen()
{
    return teamsSelectedPen;
}
