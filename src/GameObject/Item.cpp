/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Item
*/

#include "Item.hpp"

void game_object::Item::draw()
{
    static auto __bb = RAYLIB::MeshBoundingBox(_model._model.meshes[0]);
    static float _z = std::abs(__bb.min.z - __bb.max.z);
    static float _x = std::abs(__bb.min.x - __bb.max.x);
    static float __varForCalculateScale = (_z > _x) ? _z : _x;
    static float scale = std::abs(0.3 / __varForCalculateScale);

    RAYLIB::Vector3 vScale = { scale, scale, scale };
    RAYLIB::Vector3 rotationAxis = { 0.0f, 1.0f, 0.0f };

    if (!isWear)
        RAYLIB::DrawModelEx(_model._model, {_pos.x, _ypos, _pos.y}, rotationAxis, 1, vScale, RAYLIB::WHITE);
}