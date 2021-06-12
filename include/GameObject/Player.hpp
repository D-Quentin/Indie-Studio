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
        void setPos(RAYLIB::Vector2 pos);
        void setPos(RAYLIB::Vector3 pos);
        void update(std::pair<float, float> gmpAxisLeft = {0, 0}, std::pair<float, float> gmpAxisRight = {0.0f, 0.0f});
        void gest(Client *&client);
        std::string serialize();
        void deserialize(std::string);
        RAYLIB::Vector2 getPos() {return _pos;};
        float _rota;

    protected:
    private:
        bool _me;
        RAYLIB::Vector2 _pos;
        float _ypos = 0;
        rl::Models _model;
};

#endif /* !PLAYER_HPP_ */
