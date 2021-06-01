#include "EntityObjects.hpp"

unsigned int game_object::EntityObjects::getHealth()
{
    return this->_health;
}

misc::Direction game_object::EntityObjects::getDirection()
{
    return this->_direction;
}

void game_object::EntityObjects::setPosition(std::vector<double>newPosition)
{
    this->_currentPosition[0] = newPosition[0];
    this->_currentPosition[1] = newPosition[1];
}