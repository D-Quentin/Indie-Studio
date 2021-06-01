/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** GameObject
*/

#include "GameObject.hpp"

GameObject::GameObject(Vector2 pos, int id) : _pos(pos), _id(id)
{
}

Vector2 GameObject::getPos()
{
    return (this->_pos);
}

void GameObject::setPosition(Vector2 pos)
{
    this->_pos = pos;
}

int GameObject::getId()
{
    return (this->_id);
}

void GameObject::setId(int id)
{
    this->_id = id;
}

