/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Model
*/

#include "Model.hpp"

rl::Models::Models(Mesh mesh, Texture2D texture)
{
    _model = LoadModelFromMesh(mesh);
    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    _height = texture.height;
    _width = texture.width;
}

void rl::Models::draw()
{
    DrawModel(_model, { 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);
}