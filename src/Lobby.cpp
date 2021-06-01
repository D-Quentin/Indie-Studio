/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Lobby
*/

#include "Lobby.hpp"

Lobby::Lobby()
{
}

Lobby::~Lobby()
{
}

GamePhase Lobby::launch()
{
    this->_phase = JoinPhase;

    return (this->restart());
}

GamePhase Lobby::restart()
{
    GamePhase gamePhase = MenuPhase;

    switch (this->_phase) {
    case Lobby::MainPhase:
        gamePhase = this->mainPhase(gamePhase);
        break;
    case Lobby::JoinPhase:
        gamePhase = this->joinPhase(gamePhase);
        break;

    default:
        break;
    }
    return (gamePhase);
}

GamePhase Lobby::mainPhase(GamePhase gamePhase)
{
    for (auto it = this->_obj.begin(); it != this->_obj.end() ; it++) {
        it->second->draw();
    }
    return (gamePhase);
}

GamePhase Lobby::joinPhase(GamePhase gamePhase)
{
    return (gamePhase);
}
