/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Lobby
*/

#ifndef LOBBY_HPP_
#define LOBBY_HPP_

#include "Button.hpp"
#include "InputButton.hpp"
#include "Game.hpp"
#include "encapsulation.hpp"
#include "Player.hpp"
#include "Client.hpp"
#include <map>
#include <memory>

class Lobby {
    enum Phase {
        MainPhase,
        JoinPhase
    };
    public:
        Lobby();
        ~Lobby();
        GamePhase launch(Client *&, std::string, std::string);
        GamePhase restart(Client *&, std::string, std::string);
        GamePhase mainPhase(GamePhase, Client *&);
        GamePhase joinPhase(GamePhase, Client *&, std::string, std::string);

    protected:
    private:
        Phase _phase;
        std::map<int, GameObject *> _obj;
        int _player;
        int _readyPlayer;
        Client *_client;
        size_t _me;
        rl::Camera _TopCamera;
        int _renderDistance = 40;

        Button _bReady;
        rl::Text _tReady;
        rl::Text _tLoading;
};

#endif /* !LOBBY_HPP_ */