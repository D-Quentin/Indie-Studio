#include "EntityObjects.hpp"

int EntityObjects::getHealth()
{
    return this->_health;
}

void EntityObjects::draw()
{
    RAYLIB::Vector3 vScale = {_scale , _scale, _scale};
    RAYLIB::Vector3 rotationAxis = { 0.0f, 1.0f, 0.0f };
    auto pos = this->getPos();

    RAYLIB::DrawModelEx(_model._model, {pos.x, 0, pos.y}, rotationAxis, _rota, vScale, RAYLIB::GRAY);
}