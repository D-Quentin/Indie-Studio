/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Game
*/

#include "Game.hpp"
#include "Menu.hpp"

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
        
        default:
            break;
        }
        win.clear();
    }
    
}