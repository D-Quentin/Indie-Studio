/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Player
*/

#include "Player.hpp"
#include <string>

Player::Player(RAYLIB::Vector2 pos, int id, bool me) : _me(me)
{
    std::string path("/home/THE/texture/");
    float size = 0.25;
    auto mesh = RAYLIB::GenMeshCube(size, size, size);
    auto texture = RAYLIB::LoadTexture(std::string(path + "texture_minecraft_stone.png").c_str());
    this->setPos(pos);
    _model = rl::Models(mesh, texture);
    this->_rota = 0;
    this->_change = false;
    this->_id = id;
}

void Player::draw()
{
    RAYLIB::Vector3 vScale = { 1, 1, 1 };
    RAYLIB::Vector3 rotationAxis = { 0.0f, 1.0f, 0.0f };
    auto pos = this->getPos();

    RAYLIB::DrawModelEx(_model._model, {pos.x, 0, pos.y}, rotationAxis, _rota, vScale, RAYLIB::BLUE);
}

void Player::update(std::pair<float, float> move, std::pair<float, float> rota)
{
    static float oldMousePos = RAYLIB::GetMousePosition().x;
    float mousePos = RAYLIB::GetMousePosition().x;
    float speed = 5;

    if (RAYLIB::IsKeyDown(RAYLIB::KEY_LEFT_SHIFT))
        speed += 1.5;
    auto pos = this->getPos();
    if (move == std::make_pair(0.0f, 0.0f)) {
        move.second += RAYLIB::IsKeyDown(RAYLIB::KEY_D) - RAYLIB::IsKeyDown(RAYLIB::KEY_A);
        move.first += RAYLIB::IsKeyDown(RAYLIB::KEY_W) - RAYLIB::IsKeyDown(RAYLIB::KEY_S);
        move.first *= RAYLIB::GetFrameTime();
        move.second *= RAYLIB::GetFrameTime();
        move.first *= speed;
        move.second *= speed;
        move.first += pos.x;
        move.second += pos.y;
    }
    this->setPos((RAYLIB::Vector2){move.first, move.second});
    
    if (rota.second == 0)
        rota.second = oldMousePos - mousePos;;
    _rota += rota.second;
    // std::cout << "mouse :" << oldMousePos - mousePos << std::endl;
    oldMousePos = mousePos;
}

void Player::move()
{
    if (RAYLIB::IsKeyDown(RAYLIB::KEY_W))
        this->_pos.y -= 1, this->_change = true;
    if (RAYLIB::IsKeyDown(RAYLIB::KEY_S))
        this->_pos.y += 1, this->_change = true;
    if (RAYLIB::IsKeyDown(RAYLIB::KEY_A))
        this->_pos.x -= 1, this->_change = true;
    if (RAYLIB::IsKeyDown(RAYLIB::KEY_D))
        this->_pos.x += 1, this->_change = true;
}

std::string Player::serialize()
{
    std::string str;

    str += "PLAYER;ID:" + std::to_string(this->_id);
    str += ";X:" + std::to_string(this->_pos.x);
    str += ";Y:" + std::to_string(this->_pos.y);

    return (str += ";\n");
}

void Player::deserialize(std::string str)
{
    int pos = 0;

    pos = str.find("ID:");
    this->_id = std::atoi(str.substr((pos + 3), str.find(";", pos) - pos).c_str());
    pos = str.find("X:");
    this->_pos.x = std::atoi(str.substr((pos + 2), str.find(";", pos) - pos).c_str());
    pos = str.find("Y:");
    this->_pos.y = std::atoi(str.substr((pos + 2), str.find(";", pos) - pos).c_str());
}

void Player::gest(Client *&client)
{
    this->move();

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