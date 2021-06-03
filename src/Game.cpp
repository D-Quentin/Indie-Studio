/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Game
*/

#include "Game.hpp"
#include "Menu.hpp"
#include "Lobby.hpp"

Game::Game()
{
}

Game::~Game()
{
}

void Game::launch(rl::Window win)
{
    GamePhase statut = MenuPhase;
    std::pair<bool, Menu> menu = {false, Menu()};
    std::pair<bool, Lobby> lobby = {false, Lobby()};

    while (statut != QuitPhase && win.loop()) {
        switch (statut) {
        case MenuPhase:
            if (menu.first)
                statut = menu.second.restart();
            else {
                statut = menu.second.launch();
                menu.first = true;
            }
            break;
        case LobbyPhase:
            if (lobby.first)
                statut = lobby.second.restart(this->_client, menu.second.getIp(), menu.second.getPort());
            else {
                statut = lobby.second.launch(this->_client, menu.second.getIp(), menu.second.getPort());
                lobby.first = true;
            }
            break;

        default:
            break;
        }
        win.clear();
    }
    
}