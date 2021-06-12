/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Weapon
*/

#include "Weapon.hpp"

// Bullet::Bullet(RAYLIB::Vector3 pos, float rota)
// {
//     // (void) pos;
//     // (void) rota;
// }

Bullet Weapon::shoot()
{
    if (!this->_wear || !this->_nbBullet)
        return Bullet(this->_pos, this->_rota);
    this->_nbBullet -= 1;
    return Bullet(this->_pos, this->_rota);
}

void Weapon::update(RAYLIB::Vector2 pos, float rota)
{
    if (!_wear)
        return;
    this->_rota = rota;
    this->_pos.x = pos.x;
    this->_pos.z = pos.y;
    this->_pos.z += 0.10;
}

Pistol::Pistol(RAYLIB::Vector2 pos, unsigned short nbBullet)
{
    std::string path("/home/THE/texture/");
    float size = 0.1;
    auto mesh = RAYLIB::GenMeshCube(size, size, size);
    auto texture = RAYLIB::LoadTexture(std::string(path + "texture_minecraft_stone.png").c_str());

    _model = rl::Models(mesh, texture);
    this->_nbBullet = nbBullet;
    this->_pos = {pos.x, 0.5, pos.y};
    this->_pos.z += 0.1;
}

void Pistol::draw()
{
    RAYLIB::Vector3 vScale = { 1, 1, 1 };
    RAYLIB::Vector3 rotationAxis = { 0.0f, 1.0f, 0.0f };

    RAYLIB::DrawModelEx(_model._model, _pos, rotationAxis, _rota, vScale, RAYLIB::GREEN);
}