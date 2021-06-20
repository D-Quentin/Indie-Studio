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
#include "Pause.hpp"
#include "End.hpp"

static int signalStatus = 0;

Game::Game()
{
}

Game::~Game()
{
}

void signal_handler(int signal)
{
    if (signal != 0)
        signalStatus = signal;
}

void Game::launch(rl::Window win)
{
    static rl::Sound music = rl::Sound();
    GamePhase statut = MenuPhase;
    std::pair<bool, Menu> menu = {false, Menu()};
    std::pair<bool, Lobby> lobby = {false, Lobby()};
    std::pair<bool, GamePlay> gameplay = {false, GamePlay()};
    std::pair<bool, Play> play = {false, Play()};
    std::pair<bool, Setting> setting = {false, Setting()};
    std::pair<bool, Pause> pause = {false, Pause()};
    std::pair<bool, End> end = {false, End()};

    #if not defined(_WIN32)
        std::signal(SIGINT, signal_handler);
    #endif
    while (statut != QuitPhase && win.loop()) {
        if (statut == RestartPhase)
            break;
        RAYLIB::BeginDrawing();
        win.clear({255, 255, 255, 255});
        if (signalStatus != 0)
            statut = QuitPhase;
        if (RAYLIB::IsKeyPressed(RAYLIB::KEY_F6))
            statut = GamePlayPhase;
        switch (statut) {
        case MenuPhase:
            if (menu.first)
                statut = menu.second.restart();
            else {
                music.stopAllMusic();
                music.playMenuMusic();
                statut = menu.second.launch();
                menu.first = true;
            }
            break;
        case LobbyPhase:
            if (lobby.first)
                statut = lobby.second.restart(this->_client, menu.second.getIp(), menu.second.getPort());
            else {
                music.stopAllMusic();
                music.playGameMusic();
                statut = lobby.second.launch(this->_client, menu.second.getIp(), menu.second.getPort());
                lobby.first = true;
            }
            break;
        case GamePlayPhase:
            if (gameplay.first)
                statut = gameplay.second.restart();
            else {
                music.stopAllMusic();
                music.playGameMusic();
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
        case PausePhase:
            if (pause.first)
                statut = pause.second.restart();
            else {
                statut = pause.second.launch();
                pause.first = true;
            }
            break;
        case EndPhase:
            if (end.first)
                statut = end.second.restart("name");
            else {
                music.stopAllMusic();
                music.playEndMusic();
                statut = end.second.launch("name");
                end.first = true;
            }
            break;
        case SettingPhase:
            if (setting.first)
                statut = setting.second.restart();
            else {
                statut = setting.second.launch();
                setting.first = true;
            }
            break;
        default:
            break;
        }
        RAYLIB::EndDrawing();
    }
    if (lobby.second.isHost())
        this->_client->send(CLOSING_SERVER);
    else if (lobby.second.getMe() != -1)
        this->_client->send(CLIENT_CLOSING_CONNECTION);
    #if defined (DEBUG)
        std::cout << "Quiting" << std::endl;
    #endif
    if (statut == RestartPhase)
        this->launch(win);
}