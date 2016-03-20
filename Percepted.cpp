#include "Percepted.h"

Percepted::Percepted(std::shared_ptr<Entity> entity, double distance) : m_entity(entity), m_distance(distance)
{}

Percepted::Percepted()
{
    m_entity = nullptr;
    m_distance = 0;
}

void Percepted::set(std::shared_ptr<Entity> entity, double distance)
{
    m_entity = entity;
    m_distance = distance;
}
