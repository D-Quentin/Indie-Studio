/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Play
*/

#include "Play.hpp"

Play::Play()
{
}

Play::~Play()
{
}

GamePhase Play::launch(Client *&client, Lobby &lobby)
{

    return (this->restart(client, lobby));
}

GamePhase Play::restart(Client *&client, Lobby &lobby)
{
    GamePhase phase = PlayPhase;

    return (phase);
}

GamePhase Play::mainPhase(GamePhase gamePhase, Client *&client)
{

    return (gamePhase);
}

GamePhase Play::joinPhase(GamePhase gamePhase, Client *&client, Lobby &lobby)
{

    return (gamePhase);
}