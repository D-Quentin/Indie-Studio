/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Lobby
*/

#include "Lobby.hpp"
#include <string>
#include "Server.hpp"

Lobby::Lobby()
{
    this->_me = -1;
}

Lobby::~Lobby()
{
}

GamePhase Lobby::launch(Client *client, std::string ip, std::string port)
{
    this->_phase = JoinPhase;

    this->_bReady = Button(WIN_WIDTH / 2 - 300, 550, 600, 200);
    this->_tReady = rl::Text(""/*"Ready  " + std::to_string(this->_readyPlayer) + "/" + std::to_string(this->_player))*/, WIN_WIDTH / 2 - 150, 170, 150, RAYLIB::LIGHTGRAY);
    this->_tLoading = rl::Text("Loading ...", 50, 1000, 60, RAYLIB::LIGHTGRAY);

    return (this->restart(client, ip, port));
}

GamePhase Lobby::restart(Client *client, std::string ip, std::string port)
{
    GamePhase gamePhase = LobbyPhase;

    switch (this->_phase) {
    case Lobby::MainPhase:
        gamePhase = this->mainPhase(gamePhase);
        break;
    case Lobby::JoinPhase:
        gamePhase = this->joinPhase(gamePhase, client, ip, port);
        break;

    default:
        break;
    }
    return (gamePhase);
}

GamePhase Lobby::mainPhase(GamePhase gamePhase)
{
    GameObject::gestData(this->_obj, this->_client->read(), this->_client);
    ((Player *)this->_obj[this->_me])->gest();
    RAYLIB::DrawRectangle(0, 0, WIN_WIDTH, WIN_HEIGHT, RAYLIB::GRAY);
    for (auto it = this->_obj.begin(); it != this->_obj.end() ; it++) {
        it->second->draw();
    }
    return (gamePhase);
}

GamePhase Lobby::joinPhase(GamePhase gamePhase, Client *client, std::string ip, std::string port)
{
    std::cout << "Connecting to Ip: " << ip << " / Port: " << port << std::endl;
    client = new Client(ip, std::atoi(port.c_str()));
    this->_client = client;
    this->_client->launch();
    this->_client->send(INCOMMING_CONNECTION);
    this->_tLoading.draw();

    auto time = timeNow;
    std::string str = this->_client->getReponse();
    if (str == TIMEOUT_CONNECTION) { // GESTION ERREUR
        std::cout << "First connexion time out" << std::endl;
        return (QuitPhase);
    }
    time = timeNow;
    while (Chrono(time) < 1000) {
        str = client->read();
        if (str.empty() == false)
            GameObject::gestData(this->_obj, str, client);
    }
    this->_me = this->_obj.size();
    client->send("PLAYER;ID:" + std::to_string(this->_me) + ";X:500;Y:500;\n");
    this->_phase = MainPhase;
    return (gamePhase);
}
