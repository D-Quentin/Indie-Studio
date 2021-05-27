/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** model
*/

#ifndef MODEL_HPP_
#define MODEL_HPP_

#include <raylib>

class model
{
    public:
        model(Mesh, Texture2D);
        ~model() = default;

        void draw();
        Model _model;
        int _height;
        int _width;
};

model::model(Mesh mesh, Texture2D texture)
{
    _model = LoadModelFromMesh(mesh);
    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    _height = texture.height;
    _width = texture.width;
}

void model::draw()
{
    DrawModel(_model, { 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);
}

#endif /* !MODEL_HPP_ */
