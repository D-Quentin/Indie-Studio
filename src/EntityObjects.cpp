#include "EntityObjects.hpp"

unsigned int game_object::getHealth()
{
    return this->_health;
}

Direction game_object::getDirection()
{
    return this->_direction;
}

void game_object::SetPosition(std::vector<double>newPosition)
{
    this->_currentPosition[0] = newPosition[0];
    this->_currentPosition[1] = newPosition[1];
}