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
    GamePhase launch(std::string winner);
    GamePhase restart(std::string winner);
    GamePhase endPhase(GamePhase, std::string winner);
private:
    RAYLIB::Texture2D _tbackground;
    RAYLIB::Texture2D _tRocket;
    RAYLIB::Texture2D _tVictory;
    Button _bReturn;
    rl::Text _tReturn;
    rl::Text _tName;
    Button _bAgain;
    rl::Text _tAgain;
};

#endif
