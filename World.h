#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "Entity.h"

/*
 * The world is... the world
 */
class World
{
public:
    //Public methods

    // THE CONSTRUCTOR OF THE WORLD ! MOUHAHAHAHAHAAAAAAAAAAAAAAAAA !
    World();

    //Do you wanna get my entities ?
    std::vector<Entity*> & getEntities();

    //Why do you want it ? I'm the biggest world of all worlds !
    Coordinate & getSize();
    //What did I just told you ? It's useless !
    int getSizeX() const;
    //You sir are hopeless...
    int getSizeY() const;

    bool isCollision(const Entity* e) const;

    //More ! Give me more of them !
    void addEntity(Entity * entity);

    //I'm also almost the master of the time, I can make the world tic for you !
    int tic();
    int tic(int ticsNum);

private:
    //Privates methods
    bool isCollision(const Entity* e1, const Entity* e2) const;

    //Private attributes

    //My loves, my life
    std::vector<Entity*> m_entities;
    Coordinate m_size;
};

#endif // WORLD_H
