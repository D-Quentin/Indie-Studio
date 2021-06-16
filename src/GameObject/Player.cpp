/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Player
*/

#include "Player.hpp"
#include <string>
#include <Weapon.hpp>

float Vector2Angle(RAYLIB::Vector2 v1, RAYLIB::Vector2 v2)
{
    float result = atan2f(v2.y - v1.y, v2.x - v1.x)*(180.0f/PI);
    if (result < 0) result += 360.0f;
    return result;
}

Player::Player(RAYLIB::Vector2 pos, int id, bool me) : _me(me)
{
    static auto globalPlayerModel = rl::Models("assets/character/character.obj");
    static auto __bb = RAYLIB::MeshBoundingBox(globalPlayerModel._model.meshes[0]);
    static float __varForCalculateScale = __bb.min.z - __bb.max.z;
    _scale = 0.3 / __varForCalculateScale;
    this->setPos(pos);
    _model = globalPlayerModel;

    this->_rota = 0;
    this->_change = false;
    this->_id = id;
}

void Player::move()
{
    if (!RAYLIB::IsKeyDown(RAYLIB::KEY_W) && !RAYLIB::IsKeyDown(RAYLIB::KEY_S) &&
    !RAYLIB::IsKeyDown(RAYLIB::KEY_D) && !RAYLIB::IsKeyDown(RAYLIB::KEY_A))
        return;

    std::pair<float, float> move(0, 0);
    float speed = 5;
    RAYLIB::Vector2 pos = this->getPos();

    if (RAYLIB::IsKeyDown(RAYLIB::KEY_LEFT_SHIFT))
        speed += 1.5;
    if (move == std::make_pair(0.0f, 0.0f)) {
        move.first += RAYLIB::IsKeyDown(RAYLIB::KEY_W) - RAYLIB::IsKeyDown(RAYLIB::KEY_S);
        move.second += RAYLIB::IsKeyDown(RAYLIB::KEY_D) - RAYLIB::IsKeyDown(RAYLIB::KEY_A);
        move.first *= RAYLIB::GetFrameTime();
        move.second *= RAYLIB::GetFrameTime();
    }
    RAYLIB::Vector2 toSet = {pos.x + move.first * speed, pos.y + move.second * speed };
    this->_pos = toSet;
    this->_change = true;
}

void Player::dash()
{
    auto pos = getPos();
    std::pair<float, float> circlePos = pointInACircle(std::abs(_rota + 90), 0.0025);
    this->_pos.x += circlePos.first;
    this->_pos.y += circlePos.second;
}

void Player::rotate()
{
    float newRota = -Vector2Angle({(float)RAYLIB::GetScreenWidth() / 2, (float)RAYLIB::GetScreenHeight() / 2}, RAYLIB::GetMousePosition());

    if (this->_rota == newRota)
        return;
    this->_rota = newRota - 180;
    this->_change = true;
}

std::string Player::serialize()
{
    std::string str;

    str += "PLAYER;ID:" + std::to_string(this->_id);
    str += ";X:" + std::to_string(this->_pos.x);
    str += ";Y:" + std::to_string(this->_pos.y);
    str += ";R:" + std::to_string(this->_rota);

    return (str += ";\n");
}

void Player::deserialize(std::string str)
{
    int pos = 0;

    pos = str.find("ID:");
    this->_id = std::atof(str.substr((pos + 3), str.find(";", pos) - pos).c_str());
    pos = str.find("X:");
    this->_pos.x = std::atof(str.substr((pos + 2), str.find(";", pos) - pos).c_str());
    pos = str.find("Y:");
    this->_pos.y = std::atof(str.substr((pos + 2), str.find(";", pos) - pos).c_str());
    pos = str.find("R:");
    this->_rota = std::atof(str.substr((pos + 2), str.find(";", pos) - pos).c_str());
}

void Player::gest(Client *&client)
{
    // this->update();
    this->move();
    this->rotate();

    if (this->_change) {
        client->send(this->serialize());
        this->_change = false;
    }
}