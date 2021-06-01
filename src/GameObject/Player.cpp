/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(Vector2 pos, int id, bool me) : _me(me)
{
}

Player::~Player()
{
}

void Player::draw()
{
    if (this->_me)
        DrawRectangle(this->_pos.x, this->_pos.y, 50, 50, ORANGE);
    else
        DrawRectangle(this->_pos.x, this->_pos.y, 50, 50, BLUE);
}

void Player::move()
{
    if (IsKeyDown(KEY_Z))
        this->_pos.y -= 1;
    if (IsKeyDown(KEY_S))
        this->_pos.y += 1;
    if (IsKeyDown(KEY_Q))
        this->_pos.x -= 1;
    if (IsKeyDown(KEY_D))
        this->_pos.x += 1;
}

std::string Player::serialize()
{
    std::string str;

    str += "PLAYER;ID:" + std::to_string(this->_id);
    str += ";X:" + std::to_string(this->_pos.x);
    str += ";Y:" + std::to_string(this->_pos.y);

    return (str += "\n");
}

void Player::deserialize(std::string str)
{
    int pos = 0;

    pos = str.find("X:");
    this->_pos.x = std::atoi(str.substr((pos + 2), str.find(";", pos) - pos).c_str());
    pos = str.find("Y:");
    this->_pos.y = std::atoi(str.substr((pos + 2), str.find(";", pos) - pos).c_str());
}