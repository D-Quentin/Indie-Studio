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
    _rota = rota - 90;
    _a = coefDirector({this->_pos.x, this->_pos.z}, pointInACircle(this->_rota, 1));
    float y = _a * 2;
    float total = y + 2;
    _x_ref = 2 * 100 / total;
    _y_ref = _x_ref - 100;
}

void Bullet::update()
{
    float bullet_speed = 0.7;

    auto pt = pointInACircle(this->_rota, (bullet_speed * RAYLIB::GetFrameTime()));
    this->_pos.x += pt.first;
    this->_pos.z -= pt.second;
}

void Bullet::draw()
{
    RAYLIB::DrawModel(_model._model, _pos, 1, RAYLIB::GREEN);
}

Bullet Weapon::shoot()
{
    if (!this->_wear || !this->_nbBullet)
        return Bullet();
    this->_nbBullet -= 1;

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

std::string Weapon::serialize()
{
    std::string result = "###WEAPON:" + _type + "####\n";

    result += "###POSITION:X:" + std::to_string(_pos.x) + ";Y:" + std::to_string(_pos.y) + ";Z:" + std::to_string(_pos.z) + "####\n";

    return result;
}

void Weapon::deserialize(std::string str)
{
    std::string tmp;
    std::size_t id;

    while ((id = str.find("\n")) != std::string::npos) {
        tmp = str.substr(0, id);
        str.erase(0, id + 1);
        if (tmp.find("WEAPON:"))
            _type = tmp.substr(tmp.find(":") + 1, tmp.find("####"));
        else if (tmp.find("POSITION:")) {
            _pos.x = std::atof(tmp.substr(tmp.find("X:") + 2, tmp.find(";Y")).c_str());
            _pos.y = std::atof(tmp.substr(tmp.find("Y:") + 2, tmp.find(";Z")).c_str());
            _pos.z = std::atof(tmp.substr(tmp.find("Z:") + 2, tmp.find("####")).c_str());
        }
    }
    if (_type == "pistol")
        *this = Pistol({_pos.x, _pos.z});
}

Pistol::Pistol(RAYLIB::Vector2 pos)
{
    std::string path("/home/THE/texture/");
    float size = 0.1;
    auto mesh = RAYLIB::GenMeshCube(size, size, size);
    auto texture = RAYLIB::LoadTexture(std::string(path + "texture_minecraft_stone.png").c_str());

    _model = rl::Models(mesh, texture);
    this->_nbBullet = 21;
    this->_pos = {pos.x, size, pos.y};
    this->_time_shoot = 0.2f;
    this->_bullet_speed = 0.7f;
    _type = "pistol";
}

void Pistol::draw()
{
    RAYLIB::Vector3 vScale = { 1, 1, 1 };
    RAYLIB::Vector3 rotationAxis = { 0.0f, 1.0f, 0.0f };

    RAYLIB::DrawModelEx(_model._model, _pos, rotationAxis, _rota, vScale, RAYLIB::GREEN);
}