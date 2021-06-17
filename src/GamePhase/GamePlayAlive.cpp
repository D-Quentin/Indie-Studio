/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** GamePlayAlive
*/

#include "GamePlay.hpp"

void GamePlay::testThings()
{
    if (RAYLIB::IsKeyPressed(RAYLIB::KEY_KP_0))
        _weapon = new Pistol();
    else if (RAYLIB::IsKeyPressed(RAYLIB::KEY_KP_1))
        _weapon = new Rifle();
    else if (RAYLIB::IsKeyPressed(RAYLIB::KEY_KP_2))
        _weapon = new Snip();
    else if (RAYLIB::IsKeyPressed(RAYLIB::KEY_KP_3))
        _power_up.push_back(new Dash);
    else if (RAYLIB::IsKeyPressed(RAYLIB::KEY_KP_4))
        _power_up.push_back(new Shield);
    else if (RAYLIB::IsKeyPressed(RAYLIB::KEY_KP_5))
        _power_up.push_back(new Speed);
}

bool compare(PowerUp *f, PowerUp *s)
{
    return f->getPower() == s->getPower();
}

void GamePlay::updatePowerUp()
{
    _power_up.unique(compare);
    for (auto &it : _power_up)
        switch (it->getPower()) {
            case PUSpeed:
                _player.setSpeed(it->update());
                break;
            case PUShield:
                _player.setShield();
                it->use();
                break;
            case PUView:
                it->update();
                break;
            case PUDash:
                if (RAYLIB::IsKeyPressed(RAYLIB::KEY_ENTER)) {
                    _player.dash();
                    it->use();
                }
                break;
            case PUNothing:
                break;
        }
}

void GamePlay::updateLocal()
{
    //update player
    bool col = false;
    bool bullet_player = true;

    this->_player.move();
    // handle player / block colision
    for (auto it : _blocks) {
        auto playerPos = _player.getPos();
        float player_radius = 0.3f;
        auto blockPos = it->getPos();
        RAYLIB::Rectangle blockPhysic = {blockPos.x, blockPos.y, 1, 1};
        bool col = RAYLIB::CheckCollisionCircleRec(playerPos, player_radius, blockPhysic);

        if (col)
            _player.setPos(_oldPlayerPos);
        //check collision bullet  /walls
        for (auto &it : _bullet) {
            if (RAYLIB::CheckCollisionCircleRec(it.getPos(), 0.05, blockPhysic))
                it.isReal = false;
            else if (bullet_player) {
                if (RAYLIB::CheckCollisionCircles(it.getPos(), 0.05, playerPos, player_radius)) {
                    it.isReal = false;
                    _player.takeDamage(it.getDamage());
                }
            }
        }
        bullet_player = false;
    }
    this->delFalseBullet();
    //end collision
    this->_player.rotate();
    ///update weapon
    _weapon->update(_player.getPos(), _player._rota);
    if (RAYLIB::IsKeyDown(RAYLIB::KEY_SPACE))
        _bullet.push_back(_weapon->shoot());
    

    //update camera
        auto ppos = this->_player.getPos();
        ACTIVE_CAMERA.updateCamera({ppos.x, ppos.y});
}

void GamePlay::delFalseBullet()
{
    for (auto &it : _bullet)
        if (!it.isReal) {
            _bullet.remove(it);
            // this->delFalseBullet();
            break;
        }
}