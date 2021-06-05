/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Model
*/

#include "Model.hpp"

rl::Models::Models(RAYLIB::Mesh mesh, RAYLIB::Texture2D texture)
{
    _model = RAYLIB::LoadModelFromMesh(mesh);
    _model.materials[0].maps[RAYLIB::MATERIAL_MAP_DIFFUSE].texture = texture;
    _height = texture.height;
    _width = texture.width;
}

void rl::Models::draw()
{
    RAYLIB::DrawModel(_model, { 0.0f, 0.0f, 0.0f }, 1.0f, RAYLIB::WHITE);
}