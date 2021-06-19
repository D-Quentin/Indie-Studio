/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** End
*/

#ifndef END_HPP_
#define END_HPP_

#include "Game.hpp"
#include "Button.hpp"
#include "encapsulation.hpp"
#include "InputButton.hpp"
#include "Server.hpp"

class End
{
public:
    End();
    ~End();
    GamePhase launch();
    GamePhase restart();
    GamePhase endPhase(GamePhase);
private:
    RAYLIB::Texture2D _tbackground;
};

#endif
