/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** PowerUp
*/

#ifndef POWERUP_HPP_
#define POWERUP_HPP_

#define TIMENOW std::chrono::high_resolution_clock::now()
#define CHRONO(x) std::chrono::duration_cast<std::chrono::milliseconds>(TIMENOW - x).count()

#include "Item.hpp"

enum EnumPowerUp {
    PUNothing = 0,
    PUSpeed,
    PUShield,
    PUView,
    PUDash
};

class PowerUp {
    public:
        ~PowerUp();
        void use() {_type = PUNothing;};
        void update() {
            static auto start = TIMENOW;
            if (CHRONO(start) >= this->_time * 1000)
                this->_type = PUNothing;
        };
        EnumPowerUp getPower() const {return _type;};

    protected:
        EnumPowerUp _type;
        unsigned short _time;
};


class Speed : public PowerUp
{
    public:
        Speed() {_type = PUSpeed; _time = 15;};
        ~Speed() = default;
};

class Shield : public PowerUp
{
    public:
        Shield() {_type = PUShield; _time = 0;};
        ~Shield() = default;
};

class View : public PowerUp
{
    public:
        View() {_type = PUView; _time = 10;};
        ~View() = default;
};

class Dash : public PowerUp
{
    public:
        Dash() {_type = PUDash; _time = 0;};
        ~Dash() = default;
};

#endif /* !POWERUP_HPP_ */
