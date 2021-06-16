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
        void move();
        void rotate();
        void gest(Client *&client);
        std::string serialize();
        void deserialize(std::string);
<<<<<<< HEAD
        RAYLIB::Vector2 getPos() {return _pos;};
        void setShield() {_shield = true;};
        void dash();
        float _rota;
        rl::Models _model;
=======
>>>>>>> dd5ae18233f3d5c0067eadf6c9a2f34fe5a7f448

    protected:
    private:
        bool _me;
<<<<<<< HEAD
        bool _shield = false;
        RAYLIB::Vector2 _pos;
        float _ypos = 0;
        float _scale;
=======
>>>>>>> dd5ae18233f3d5c0067eadf6c9a2f34fe5a7f448
};

#endif /* !PLAYER_HPP_ */
