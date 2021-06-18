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
    this->_weapon1 = new Pistol();
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
        speed += 1.5 + (_moreSpeed ? 2 : 0);
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
    std::pair<float, float> circlePos = pointInACircle(std::abs(_rota + 90), 1);
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

void Player::gestColision(std::list<BlockObject *> blocks, RAYLIB::Vector2 oldPlayerPos)
{
    bool bullet_player = true;

    for (auto it : blocks) {
        // With Player
        RAYLIB::Vector2 playerPos = this->_pos;
        float player_radius = 0.3f;
        RAYLIB::Vector2 blockPos = it->getPos();
        RAYLIB::Rectangle blockPhysic = {blockPos.x, blockPos.y, 1, 1};
        bool col = RAYLIB::CheckCollisionCircleRec(playerPos, player_radius, blockPhysic);

        if (col)
            this->_pos = oldPlayerPos;

        // With Bullets
        for (auto &it : _bullet) {
            if (RAYLIB::CheckCollisionCircleRec(it.getPos(), 0.05, blockPhysic))
                it.isReal = false;
            else if (bullet_player) {
                if (RAYLIB::CheckCollisionCircles(it.getPos(), 0.05, playerPos, player_radius)) {
                    it.isReal = false;
                    this->takeDamage(it.getDamage());
                }
            }
        }
        bullet_player = false;
    }
    for (auto &it : _bullet) {
        if (!it.isReal) {
            _bullet.remove(it);
            break;
        }
    }
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

void Player::gest(Client *&client, std::list<BlockObject *> blocks)
{
    RAYLIB::Vector2 oldPlayerPos = this->_pos;

    this->move();
    this->rotate();
    this->gestColision(blocks, oldPlayerPos);
    if (this->_weaponUse == 1) {
        this->_weapon1->update(this->_pos, this->_rota);
        if (RAYLIB::IsKeyDown(RAYLIB::KEY_SPACE))
            _bullet.push_back(this->_weapon1->shoot());
    } else if (this->_weaponUse == 2) {
        this->_weapon2->update(this->_pos, this->_rota);
        if (RAYLIB::IsKeyDown(RAYLIB::KEY_SPACE))
            _bullet.push_back(this->_weapon2->shoot());
    }

    if (this->_change) {
        client->send(this->serialize());
        this->_change = false;
    }
}