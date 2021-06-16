/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "EntityObjects.hpp"
#include "Model.hpp"

class Player : public EntityObjects {
    public:
        Player(RAYLIB::Vector2 = {0, 0}, int = -1, bool = false);
        ~Player() = default;
        void draw();
        void move();
        void rotate();
        void setPos(RAYLIB::Vector2 pos);
        void setPos(RAYLIB::Vector3 pos);
        void gest(Client *&client);
        std::string serialize();
        void deserialize(std::string);
        RAYLIB::Vector2 getPos() {return _pos;};
        void setShield() {_shield = true;};
        void dash();
        float _rota;
        rl::Models _model;

    protected:
    private:
        bool _me;
        bool _shield = false;
        RAYLIB::Vector2 _pos;
        float _ypos = 0;
        float _scale;
};

#endif /* !PLAYER_HPP_ */
