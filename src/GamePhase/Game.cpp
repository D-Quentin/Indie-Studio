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
#include "Play.hpp"
#include "Setting.hpp"

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
    std::pair<bool, Play> play = {false, Play()};
    std::pair<bool, Setting> setting = {false, Setting()};

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
            break;
        case PlayPhase:
            if (play.first)
                statut = play.second.restart(this->_client, lobby.second);
            else {
                statut = play.second.launch(this->_client, lobby.second);
                play.first = true;
            }
            break;
        case SettingPhase:
            if (setting.first)
                statut = setting.second.restart();
            else {
                statut = setting.second.launch();
                setting.first = true;
            }
        default:
            break;
        }
        RAYLIB::EndDrawing();
    }
    if (lobby.second.isHost())
        this->_client->send(CLOSING_SERVER);
    std::cout << "Quiting" << std::endl;
}