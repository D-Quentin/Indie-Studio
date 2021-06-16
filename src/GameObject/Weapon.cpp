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

Bullet::Bullet(RAYLIB::Vector3 pos, float rota, float cone, float damage, float speed)
{
    static RAYLIB::Mesh mesh = RAYLIB::GenMeshSphere(0.05, 16, 16);
    static RAYLIB::Texture2D texture = RAYLIB::LoadTexture("assets/weapons/Bullet/BulletsTexture.png");
    static rl::Models model = rl::Models(mesh, texture);

    rota -= 180;
    _model = model;
    _pos = pos;
    _rota = RAYLIB::GetRandomValue(rota - cone, rota + cone);
    _damage = damage;
    _speed = speed;
}

void Bullet::update(float radius)
{
    if (std::isnan(radius))
        radius = this->_speed * RAYLIB::GetFrameTime();
    auto pt = pointInACircle(this->_rota, (radius));
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
    auto toRet = Bullet(this->_pos, this->_rota, this->_cone, this->_damage, this->_bullet_speed);

    toRet.update(0.35);
    return toRet;
}

void Weapon::update(RAYLIB::Vector2 pos, float rota)
{
    if (!_wear)
        return;
    this->_rota = rota - 90;
    std::pair<float, float> circlePos = pointInACircle(std::abs(rota), 0.2);
    this->_pos.x = pos.x + circlePos.first;
    this->_pos.z = pos.y + circlePos.second;
    this->_pos.y = 0.1;
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

void Weapon::draw()
{
    float scale = 0.1;
    RAYLIB::Vector3 vScale = { scale, scale, scale };
    RAYLIB::Vector3 rotationAxis = { 0.0f, 1.0f, 0.0f };

    RAYLIB::DrawModelEx(_model._model, _pos, rotationAxis, _rota, vScale, RAYLIB::RED);
}

Pistol::Pistol(RAYLIB::Vector2 pos)
{
    std::string path("assets/weapons/Baretta/");
    static rl::Models pistol_model = rl::Models(std::string(path + "Beretta.obj"));

    _model = pistol_model;
    this->_nbBullet = 21;
    this->_pos = {pos.x, 0.1, pos.y};
    this->_time_shoot = 0.2f;
    this->_bullet_speed = 1.5f;
    this->_damage = 20;
    this->_cone = 5;
    _type = "pistol";
}

bool operator==(Bullet f, Bullet s)
{
    auto fPos = f.getPos();
    auto sPos = s.getPos();

    if (fPos.x == sPos.x && fPos.y == sPos.y)
        return true;
    return false;
}