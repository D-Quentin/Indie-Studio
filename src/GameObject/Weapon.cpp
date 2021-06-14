/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Weapon
*/

#include "Weapon.hpp"
#include <cmath>

std::pair<float, float> pointInACircle(float angle, float radius)
{

    angle *= PI;

    float x = radius * std::cos(angle / 180);
    float y = radius * std::sin(angle / 180);

    return {x, y};
}

float coefDirector(std::pair<float, float> origine, std::pair<float, float> nextPoint)
{
    float x = nextPoint.first + origine.first;
    float y = nextPoint.second + origine.second;

    return y / x;
}

Bullet::Bullet()
{
    isReal = false;
}

Bullet::Bullet(RAYLIB::Vector3 pos, float rota, rl::Models model)
{
    _model = model;
    _pos = pos;
    _rota = rota;
    _a = coefDirector({this->_pos.x, this->_pos.z}, pointInACircle(this->_rota, 1));
    float y = _a * 2;
    float total = y + 2;
    _x_ref = 2 * 100 / total;
    _y_ref = _x_ref - 100;
}

void Bullet::update()
{
//     float bullet_speed = 0.2;

//     this->_pos.x += (((_x_ref / 10) * bullet_speed) * RAYLIB::GetFrameTime());
//     this->_pos.z += (((_y_ref / 10) * bullet_speed) * RAYLIB::GetFrameTime());
    auto pt = pointInACircle(this->_a, (0.2 * RAYLIB::GetFrameTime()));
    this->_pos.x += pt.first;
    this->_pos.z += pt.second;
}

void Bullet::draw()
{
    RAYLIB::DrawModel(_model._model, _pos, 1, RAYLIB::GREEN);
}

Bullet Weapon::shoot()
{
    // if (!this->_wear || !this->_nbBullet)
    //     return Bullet();
    this->_nbBullet -= 1;

    std::cout << "shoot" << std::endl;
    return Bullet(this->_pos, this->_rota, this->_model);
}

void Weapon::update(RAYLIB::Vector2 pos, float rota)
{
    if (!_wear)
        return;
    this->_rota = rota;
    std::pair<float, float> circlePos = pointInACircle(std::abs(rota), 0.2);
    this->_pos.x = pos.x + circlePos.first;
    this->_pos.z = pos.y + circlePos.second;
}

Pistol::Pistol(RAYLIB::Vector2 pos, unsigned short nbBullet)
{
    std::string path("/home/THE/texture/");
    float size = 0.1;
    auto mesh = RAYLIB::GenMeshCube(size, size, size);
    auto texture = RAYLIB::LoadTexture(std::string(path + "texture_minecraft_stone.png").c_str());

    _model = rl::Models(mesh, texture);
    this->_nbBullet = nbBullet;
    this->_pos = {pos.x, size, pos.y};
}

void Pistol::draw()
{
    RAYLIB::Vector3 vScale = { 1, 1, 1 };
    RAYLIB::Vector3 rotationAxis = { 0.0f, 1.0f, 0.0f };

    RAYLIB::DrawModelEx(_model._model, _pos, rotationAxis, _rota, vScale, RAYLIB::GREEN);
}