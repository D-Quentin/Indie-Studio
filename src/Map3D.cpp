/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** Map3D
*/

#include "Map3D.hpp"
#include "Encapsulation/Model.hpp"


//Map3D


Map3D::Map3D(std::vector<std::vector<char>> map, rl::Models model, float size)
{
    int i = 0, j = 0;

    for (const auto &itj : map) {
        i = 0;
        for (const auto &it : itj) {
            if (it == 'X')
                this->_mapBlocks.push_back(MapBlock(model, {size * i, 0, size * j}, size));
            else if (it == 'S')
                this->_spawns.push_back({size * i, size * j});
            else if (it == 'P')
                this->_items.push_back({size * i, size * j});
            i += 1;
        }
        j += 1;
    }
}

void Map3D::draw()
{
    for (auto it : _mapBlocks)
        it.draw();
}

// MapBlock

MapBlock::MapBlock(rl::Models model, RAYLIB::Vector3 pos, float size)
{
    model.setPos({pos.x, pos.y + size / 2, pos.z});
    _model = model;
    _pos = pos;
    _size = size;
    _modelSet = true;
}

void MapBlock::draw()
{
    if (_modelSet)
        _model.draw();

}