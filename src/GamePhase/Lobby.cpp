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

Lobby::Lobby()
{
    this->_me = -1;
    this->_TopCamera = rl::Camera({0, 6, 0});
}

Lobby::~Lobby()
{
}

GamePhase Lobby::launch(Client *&client, std::string ip, std::string port)
{
    this->_phase = JoinPhase;

    this->_bReady = Button(35, 50, 31, 18);
    this->_tReady = rl::Text(""/*"Ready  " + std::to_string(this->_readyPlayer) + "/" + std::to_string(this->_player))*/, 42, 9, 70, RAYLIB::LIGHTGRAY);
    this->_tLoading = rl::Text("Loading ...", 5, 92, 40, RAYLIB::LIGHTGRAY);

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
        GameObject::gestData(this->_obj, this->_client->read(), this->_client, this->_me);
        ((Player *)this->_obj[this->_me])->gest(client);
        rl::Text(std::to_string(((Player *)this->_obj[this->_me])->_rota), 10, 10, 15, {255, 0, 0, 255}).draw();
        
        RAYLIB::BeginMode3D(this->_TopCamera.getCamera());
        auto pos = ((Player *)this->_obj[this->_me])->getPos();

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
    std::cout << "Connecting to Ip: " << ip << " / Port: " << port << std::endl;
    client = new Client(ip, std::atoi(port.c_str()));
    this->_client = client;
    this->_client->launch();
    this->_client->send(INCOMMING_CONNECTION);
    this->_tLoading.draw();

    sleep(1);
    std::string str = client->read();
    if (str == "") { // GESTION ERREUR
        std::cout << "First connexion time out" << std::endl;
        return (QuitPhase);
    }
    GameObject::gestData(this->_obj, str, client, this->_me);

    std::cout << "Get Info Start" << std::endl;
    sleep(1);
    str = client->read();
    GameObject::gestData(this->_obj, str, client, this->_me);
    std::cout << "Get Info End" << std::endl;
    this->_me = this->_obj.size();

    client->send("PLAYER;ID:" + std::to_string(this->_me) + ";X:500;Y:500;\n");
    sleep(1);
    str = client->read();
    if (str == "") { // GESTION ERREUR
        std::cout << "Getting info time out" << std::endl;
        return (QuitPhase);
    }
    GameObject::gestData(this->_obj, str, client, this->_me);

    this->_phase = MainPhase;
    return (gamePhase);
}
