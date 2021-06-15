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
#include "Encapsulation/Text.hpp"

// static auto bulletModel = rl::Models("assets/weapons/Bullet/Bullet.obj");

class Bullet : public game_object::Item
{
    public :
        Bullet(RAYLIB::Vector3 pos, float rota);
        Bullet();
        ~Bullet() = default;

        void update();
        void draw();

        std::string serialize() {return std::string("");};
        void deserialize(std::string) {};

        bool isReal = true;
    private :
        RAYLIB::Vector3 _pos;
        float _x_ref;
        float _y_ref;
        float _rota;
        float _a;
        rl::Models _model;
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
        std::string serialize();
        void deserialize(std::string);

    protected:
        RAYLIB::Vector3 _pos;
        unsigned short _nbBullet;
        float _time_shoot;
        float _bullet_speed;
        std::string _type;
        float _rota;
        bool _wear = true;
        rl::Models _model;
};

class Pistol : public Weapon
{
    public :
        Pistol(RAYLIB::Vector2 pos);
        ~Pistol() = default;

        void draw();
    private:
};


#endif /* !WEAPON_HPP_ */
