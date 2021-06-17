/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** EntityObjects
*/

#include "EntityObjects.hpp"

int EntityObjects::getHealth()
{
    return this->_health;
}

void EntityObjects::draw()
{
    RAYLIB::Vector3 vScale = {_scale , _scale, _scale};
    RAYLIB::Vector3 rotationAxis = { 0.0f, 1, 0.0f };
    auto pos = this->getPos();

    RAYLIB::DrawModelEx(_model._model, {pos.x, 0, pos.y}, rotationAxis, _rota, vScale, RAYLIB::GRAY);
}

void EntityObjects::takeDamage(int damage)
{
    if (this->_shield) {
        _shield = false;
        return;
    }
    this->_health -= damage;
}