/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "EntityObjects.hpp"

class Player : public EntityObjects {
    public:
        Player(RAYLIB::Vector2 = {0, 0}, int = -1, bool = false);
        ~Player() = default;
        void draw();
        void move();
        void gest(Client *&);
        std::string serialize();
        void deserialize(std::string);

    protected:
    private:
        bool _me;
};

#endif /* !PLAYER_HPP_ */
