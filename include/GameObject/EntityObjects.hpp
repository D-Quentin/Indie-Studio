/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** EntityObjects
*/

#ifndef BOMBERMAN_ENTITYOBJECTS_HPP
#define BOMBERMAN_ENTITYOBJECTS_HPP

#include "GameObject.hpp"
#include "Model.hpp"
#include "Weapon.hpp"

class EntityObjects : public GameObject {
    public:
        EntityObjects(RAYLIB::Vector2 = {0, 0}, int = -1) {};
        ~EntityObjects() = default;

        int getHealth();
        void setShield() {_shield = true;};
        void setWeaponUse(int weapon);
        void takeDamage(int damage);
        bool isAlive() {return (_health > 0) ;};
        void draw();
        float _rota;
        rl::Models _model;

    protected:
        int _health = 100;
        float _scale;
        bool _shield = false;
        int _weaponUse = 0;
        Weapon *_weapon1;
        Weapon *_weapon2;
        std::list<Bullet> _bullet;
    };


#endif //BOMBERMAN_ENTITYOBJECTS_HPP