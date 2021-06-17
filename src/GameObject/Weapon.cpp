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
    RAYLIB::Mesh mesh = RAYLIB::GenMeshSphere(0.05, 16, 16);
    rl::Models bulletModel = rl::Models(mesh);

    rota -= 180;
    _model = bulletModel;
    this->setPos(pos);
    _rota = RAYLIB::GetRandomValue(rota - cone, rota + cone);
    _damage = (int) damage;
    _speed = speed;
    this->update(0.35);
}

void Bullet::update(float radius)
{
    if (!isReal)
        return;
    if (std::isnan(radius))
        radius = this->_speed * RAYLIB::GetFrameTime();
    auto pt = pointInACircle(this->_rota, (radius));
    this->_pos.x += pt.first;
    this->_pos.y -= pt.second;
}

void Bullet::draw()
{
    if (isReal)
        RAYLIB::DrawModel(_model._model, {_pos.x, _ypos, _pos.y}, 1, RAYLIB::BLACK);
}

Bullet Weapon::shoot()
{
    static auto lastShoot = TIMENOW;
    static bool first = true;

    if (first);
    else if (!this->_wear || !this->_nbBullet || CHRONO(lastShoot) < this->_time_shoot)
        return Bullet();
    first = false;
    lastShoot = TIMENOW;
    this->_nbBullet -= 1;

    return Bullet({this->_pos.x, _ypos, _pos.y}, this->_rota, this->_cone, this->_damage, this->_bullet_speed);;
}

void Weapon::update(RAYLIB::Vector2 pos, float rota)
{
    if (!_wear)
        return;
    this->_rota = rota - 90;
    std::pair<float, float> circlePos = pointInACircle(std::abs(rota), 0.2);
    this->_pos.x = pos.x + circlePos.first;
    this->_pos.y = pos.y + circlePos.second;
    this->_ypos = 0.1;
}

std::string Weapon::serialize()
{
    std::string result = "###WEAPON:" + _type + "####\n";

    result += "###POSITION:X:" + std::to_string(_pos.x) + ";Y:" + std::to_string(_ypos) + ";Z:" + std::to_string(_pos.y) + "####\n";

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
            _ypos = std::atof(tmp.substr(tmp.find("Y:") + 2, tmp.find(";Z")).c_str());
            _pos.y = std::atof(tmp.substr(tmp.find("Z:") + 2, tmp.find("####")).c_str());
        }
    }
    if (_type == "pistol")
        *this = Pistol({_pos.x, _pos.y});
}

void Weapon::draw()
{
    float scale = 0.1;
    RAYLIB::Vector3 vScale = { scale, scale, scale };
    RAYLIB::Vector3 rotationAxis = { 0.0f, 1.0f, 0.0f };

    RAYLIB::DrawModelEx(_model._model, {_pos.x, _ypos, _pos.y}, rotationAxis, _rota, vScale, RAYLIB::RED);
}

Pistol::Pistol(RAYLIB::Vector2 pos)
{
    std::string path("assets/weapons/Baretta/");
    static rl::Models pistol_model = rl::Models(std::string(path + "Beretta.obj"));

    _model = pistol_model;
    this->_nbBullet = 21;
    this->_pos = pos;
    _ypos = 0.1;
    this->_time_shoot = 500;
    this->_bullet_speed = 1.5f;
    this->_damage = 20;
    this->_cone = 5;
    _type = "pistol";
}

Rifle::Rifle(RAYLIB::Vector2 pos)
{
    std::string path("assets/weapons/Baretta/");
    static rl::Models rifle_model = rl::Models(std::string(path + "Beretta.obj"));

    _model = rifle_model;
    this->_nbBullet = 35;
    this->_pos = pos;
    _ypos = 0.1;
    this->_time_shoot = 100;
    this->_bullet_speed = 2;
    this->_damage = 40;
    this->_cone = 10;
    _type = "rifle";
}

Snip::Snip(RAYLIB::Vector2 pos)
{
    std::string path("assets/weapons/Baretta/");
    static rl::Models snip_model = rl::Models(std::string(path + "Beretta.obj"));

    _model = snip_model;
    this->_nbBullet = 6;
    this->_pos = pos;
    _ypos = 0.1;
    this->_time_shoot = 1500;
    this->_bullet_speed = 5;
    this->_damage = 100;
    this->_cone = 0;
    _type = "snip";
}

bool operator==(Bullet f, Bullet s)
{
    auto fPos = f.getPos();
    auto sPos = s.getPos();

    if (fPos.x == sPos.x && fPos.y == sPos.y)
        return true;
    return false;
}