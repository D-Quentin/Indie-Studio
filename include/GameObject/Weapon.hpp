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
#include <chrono>

#define TIMENOW std::chrono::high_resolution_clock::now()
#define CHRONO(x) std::chrono::duration_cast<std::chrono::milliseconds>(TIMENOW - x).count()

// static auto bulletModel = rl::Models("assets/weapons/Bullet/Bullet.obj");

class Bullet : public game_object::Item
{
    public :
        Bullet(RAYLIB::Vector3 pos, float rota, float cone, float damage, float speed);
        Bullet();
        ~Bullet() = default;

        void update(float radius = std::nanf("0"));
        void draw();
        RAYLIB::Vector2 getPos() {return {_pos.x, _pos.z};};

        std::string serialize() {return std::string("");};
        void deserialize(std::string) {};

        bool isReal = true;
    private :
        RAYLIB::Vector3 _pos;
        float _rota;
        float _damage;
        float _speed;
        rl::Models _model;
};

bool operator==(Bullet f, Bullet s);

class Weapon : public game_object::Item
{
    public:
        ~Weapon() = default;

    // //viruital
    //     virtual void draw() = 0;

    //physical (like dl)
        Bullet shoot();
        void take() {_wear = true;};
        void drop() {_wear = false;};
        void update(RAYLIB::Vector2 pos, float rota);
        std::string serialize();
        void deserialize(std::string);
        void draw();

    protected:
        RAYLIB::Vector3 _pos;
        unsigned short _nbBullet;
        float _cone;
        float _damage;
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
        Pistol();
        Pistol(RAYLIB::Vector2 pos = {0, 0});
        ~Pistol() = default;

    private:
};


#endif /* !WEAPON_HPP_ */
