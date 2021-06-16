/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Play
*/

#ifndef PLAY_HPP_
#define PLAY_HPP_

#include "Game.hpp"
#include "Player.hpp"
#include "Lobby.hpp"
#include "Ai.hpp"

class Play {
    enum Phase {
        MainPhase,
        JoinPhase
    };
    public:
        Play();
        ~Play();
        GamePhase launch(Client *&, Lobby &);
        GamePhase restart(Client *&, Lobby &);
        GamePhase mainPhase(GamePhase, Client *&);
        GamePhase joinPhase(GamePhase, Client *&, Lobby &);

    protected:
    private:
        Phase _phase;
        std::map<int, GameObject *> _obj;
        int _player;
        Client *_client;
        size_t _me;
        rl::Camera _TopCamera;
        int _renderDistance = 40;
        std::vector<Ai *> _ai;
        int _nbAi;
        std::vector<std::vector<char>> _map;
};

#endif /* !PLAY_HPP_ */
