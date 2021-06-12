/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Weapon
*/

#ifndef WEAPON_HPP_
#define WEAPON_HPP_

#include "Item.hpp"
#include "include.hpp"
#include "Model.hpp"

class Bullet : public game_object::Item
{
    public :
        Bullet(RAYLIB::Vector3 pos, float rota) {};
        ~Bullet() = default;

        void update() {};
        void draw() {};

        std::string serialize() {return std::string("");};
        void deserialize(std::string) {};

    private :
        RAYLIB::Vector3 _pos;
        float _rota;
};

class Weapon : public game_object::Item
{
    public:
        ~Weapon() = default;

    //viruital
        virtual void draw() = 0;

    //physical (like dl)
        Bullet shoot();
        void take() {_wear = true;};
        void drop() {_wear = false;};
        void update(RAYLIB::Vector2 pos, float rota);

    protected:
        RAYLIB::Vector3 _pos;
        float _rota;
        bool _wear = true;
        unsigned short _nbBullet;
};

class Pistol : public Weapon
{
    public :
        Pistol(RAYLIB::Vector2 pos, unsigned short nbBullet = 21);
        ~Pistol() = default;

        std::string serialize() {};
        void deserialize(std::string) {};

        void draw();
    private:
        rl::Models _model;
};

#endif /* !WEAPON_HPP_ */
