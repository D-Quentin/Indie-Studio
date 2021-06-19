/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** EntityObjects
*/

#include "EntityObjects.hpp"


int EntityObjects::getHealth()
{
    return this->_health;
}

void EntityObjects::draw()
{
    // Draw Player
    RAYLIB::Vector3 vScale = {_scale , _scale, _scale};
    RAYLIB::Vector3 rotationAxis = { 0.0f, 1, 0.0f };
    auto pos = this->getPos();

    RAYLIB::DrawModelEx(_model._model, {pos.x, 0, pos.y}, rotationAxis, _rota, vScale, RAYLIB::GRAY);

    // Draw Weapon
    if (this->_weaponUse == 1)
        this->_weapon1->draw();
    else if (this->_weaponUse == 2)
        this->_weapon2->draw();

    // Draw Bullets
    for (auto &it : this->_bullet) {
        it.update();
    }
    for (auto &it : this->_tmp_bullet) {
        it.update();
        it.draw();
    }
}

void EntityObjects::takeDamage(int damage)
{
    if (this->_shield) {
        _shield = false;
        return;
    }
    this->_health -= damage;
}

void EntityObjects::setWeaponUse(int weapon)
{
    this->_weaponUse = weapon;
}

void EntityObjects::createWeapon(std::string weapon, int nb)
{
    if (nb == 1) {
        if (weapon == "PISTOL")
            this->_weapon1 = new Pistol((this->_id + 1) * 1000);
        if (weapon == "RIFLE")
            this->_weapon1 = new Pistol((this->_id + 1) * 1000);
        if (weapon == "SNIP")
            this->_weapon1 = new Pistol((this->_id + 1) * 1000);
    } else {
        if (weapon == "PISTOL")
            this->_weapon2 = new Pistol((this->_id + 1) * 1000 + 1);
        if (weapon == "RIFLE")
            this->_weapon2 = new Pistol((this->_id + 1) * 1000 + 1);
        if (weapon == "SNIP")
            this->_weapon2 = new Pistol((this->_id + 1) * 1000 + 1);
    }
}