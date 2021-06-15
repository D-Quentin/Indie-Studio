/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Lobby
*/

#include "Lobby.hpp"
#include <string>
#include "Server.hpp"
#include "Encapsulation/Text.hpp"
#if defined(_WIN32)
    #include <windows.h>
#else
    #include <stdlib.h>
#endif

Lobby::Lobby()
{
    this->_me = -1;
    this->_TopCamera = rl::Camera({0, 6, 0});
    this->_player = 1;
    this->_readyPlayer = 0;
    this->_host = false;
    this->_ready = false;
}

Lobby::~Lobby()
{
}

bool Lobby::isHost(void)
{
    return (this->_host);
}

size_t Lobby::getMe(void)
{
    return (this->_me);
}

int Lobby::getReadyPlayer(void)
{
    return (this->_readyPlayer);
}

void Lobby::setReadyPlayer(int readyPlayer)
{
    this->_readyPlayer = readyPlayer;
}

int Lobby::getPlayer()
{
    return (this->_player);
}

void Lobby::setPlayer(int player)
{
    this->_player = player;
}

GamePhase Lobby::launch(Client *&client, std::string ip, std::string port)
{
    this->_phase = JoinPhase;

    this->_bReady = Button(" ", 65, 80, 30, 15);
    this->_tReady = rl::Text("Ready  " + std::to_string(this->_readyPlayer) + "/" + std::to_string(this->_player), 67, 82, 50, RAYLIB::LIGHTGRAY);

    return (this->restart(client, ip, port));
}

GamePhase Lobby::restart(Client *&client, std::string ip, std::string port)
{
    GamePhase gamePhase = LobbyPhase;

    switch (this->_phase) {
    case Lobby::MainPhase:
        gamePhase = this->mainPhase(gamePhase, client);
        break;
    case Lobby::JoinPhase:
        gamePhase = this->joinPhase(gamePhase, client, ip, port);
        break;

    default:
        break;
    }
    return (gamePhase);
}

GamePhase Lobby::mainPhase(GamePhase gamePhase, Client *&client)
{
    GameObject::gestData(this->_obj, this->_client->read(), this->_client, *this);
    ((Player *)this->_obj[this->_me])->gest(client);
    // rl::Text(std::to_string(((Player *)this->_obj[this->_me])->_rota), 10, 10, 15, {255, 0, 0, 255}).draw();
    if (!this->_ready && this->_bReady.isClicked()) {
        this->_ready = true;
        client->send("READY;\n");
    }
    this->_tReady.setText("Ready  " + std::to_string(this->_readyPlayer) + "/" + std::to_string(this->_player));

    // 2D Drawing
    this->_bReady.draw();
    this->_tReady.draw();

    // 3D Drawing
    RAYLIB::BeginMode3D(this->_TopCamera.getCamera());
    RAYLIB::Vector2 pos = ((Player *)this->_obj[this->_me])->getPos();
    _TopCamera.updateCamera({pos.x, pos.y});
    for (auto it = this->_obj.begin(); it != this->_obj.end() ; it++) {
        it->second->draw();
    }
    RAYLIB::DrawGrid(1000, 10);
    RAYLIB::EndMode3D();

    return (gamePhase);
}

GamePhase Lobby::joinPhase(GamePhase gamePhase, Client *&client, std::string ip, std::string port)
{
    rl::Window::loading();
    std::cout << "Connecting to Ip: " << ip << " / Port: " << port << std::endl;
    client = new Client(ip, std::atoi(port.c_str()));
    this->_client = client;
    this->_client->launch();
    this->_client->send(INCOMMING_CONNECTION);

    #if defined(_WIN32)
        Sleep(1000);
    #else
        sleep(1);
    #endif
    std::string str = client->read();
    if (str == "") { // GESTION ERREUR
        std::cout << "First connexion time out" << std::endl;
        return (QuitPhase);
    }
    GameObject::gestData(this->_obj, str, client, *this);

    std::cout << "Get Info Start" << std::endl;
    #if defined(_WIN32)
        Sleep(1000);
    #else
        sleep(1);
    #endif
    str = client->read();
    GameObject::gestData(this->_obj, str, client, *this);
    std::cout << "Get Info End" << std::endl;
    this->_me = this->_obj.size();
    if (this->_me == 0)
        this->_host = true;

    client->send("PLAYER;ID:" + std::to_string(this->_me) + ";X:500;Y:500;\n");
    #if defined(_WIN32)
        Sleep(1000);
    #else
        sleep(1);
    #endif
    str = client->read();
    if (str == "") { // GESTION ERREUR
        std::cout << "Getting info time out" << std::endl;
        return (QuitPhase);
    }
    GameObject::gestData(this->_obj, str, client, *this);

    this->_phase = MainPhase;
    return (gamePhase);
}