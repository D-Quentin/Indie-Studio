/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Game
*/

#include "Game.hpp"
#include "Menu.hpp"
#include "Lobby.hpp"
#include "GamePlay.hpp"


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
    std::pair<bool, GamePlay> gameplay = {false, GamePlay()};

    while (statut != QuitPhase && win.loop()) {
        RAYLIB::BeginDrawing();
        win.clear({255, 255, 255, 255});
        if (RAYLIB::IsKeyPressed(RAYLIB::KEY_F6))
            statut = GamePlayPhase;
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
        case GamePlayPhase:
            if (gameplay.first)
                statut = gameplay.second.restart();
            else {
                statut = gameplay.second.launch();
                gameplay.first = true;
            }
        default:
            break;
        }
        RAYLIB::EndDrawing();
    }
    std::cout << "Quiting" << std::endl;
}