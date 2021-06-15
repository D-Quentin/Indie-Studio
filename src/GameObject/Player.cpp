/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Player
*/

#include "Player.hpp"
#include <string>

float Vector2Angle(RAYLIB::Vector2 v1, RAYLIB::Vector2 v2)
{
    float result = atan2f(v2.y - v1.y, v2.x - v1.x)*(180.0f/PI);
    if (result < 0) result += 360.0f;
    return result;
}

Player::Player(RAYLIB::Vector2 pos, int id, bool me) : _me(me)
{
    this->setPos(pos);
    _model = rl::Models(std::string("assets/character/character.obj"));
    this->_rota = 0;
    this->_change = false;
    this->_id = id;
}

void Player::draw()
{
    float scale = 15;
    RAYLIB::Vector3 vScale = { scale, scale, scale};
    RAYLIB::Vector3 rotationAxis = { 0.0f, 1.0f, 0.0f };
    auto pos = this->getPos();

    RAYLIB::DrawModelEx(_model._model, {pos.x, 0, pos.y}, rotationAxis, _rota, vScale, RAYLIB::GRAY);
}

// void Player::update(, std::pair<float, float> rota)
// {
//     // if (!RAYLIB::IsKeyDown(RAYLIB::KEY_W) && !RAYLIB::IsKeyDown(RAYLIB::KEY_S) &&
//     // !RAYLIB::IsKeyDown(RAYLIB::KEY_D) && !RAYLIB::IsKeyDown(RAYLIB::KEY_A))
//     //     return;
//     static float oldMousePos = RAYLIB::GetMousePosition().x;
//     float mousePos = RAYLIB::GetMousePosition().x;
//     float speed = 5;
//     auto pos = this->getPos();

    

//     if (rota.second == 0)
//         rota.second = oldMousePos - mousePos;;
//     _rota += rota.second;
//     _rota = (int) _rota % 360;
//     _rota = -Vector2Angle({(float)RAYLIB::GetScreenWidth() / 2, (float)RAYLIB::GetScreenHeight() / 2}, RAYLIB::GetMousePosition());
//     oldMousePos = mousePos;
//     this->_change = true;
// }

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

void Player::rotate()
{
    float newRota = -Vector2Angle({(float)RAYLIB::GetScreenWidth() / 2, (float)RAYLIB::GetScreenHeight() / 2}, RAYLIB::GetMousePosition());

    if (this->_rota == newRota)
        return;
    this->_rota = newRota;
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
void Player::setPos(RAYLIB::Vector2 pos)
{
    this->_pos = pos;
}

void Player::setPos(RAYLIB::Vector3 pos)
{
    this->_pos = {pos.x, pos.z};
    this->_ypos = pos.y;
}