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
}

void Player::draw()
{
    if (this->_me)
        RAYLIB::DrawRectangle(this->_pos.x, this->_pos.y, 50, 50, RAYLIB::ORANGE);
    else
        RAYLIB::DrawRectangle(this->_pos.x, this->_pos.y, 50, 50, RAYLIB::BLUE);
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