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
#include "Map.hpp"
#include "Map3D.hpp"

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
        bool _host;
        size_t _me;
        rl::Camera _TopCamera;
        int _renderDistance = 40;
        std::vector<Ai *> _ai;
        int _nbAi;
        std::vector<std::vector<char>> _map;
        std::pair<float, float> _mapSize;
        std::list<BlockObject *> _blocks;
};

#endif /* !PLAY_HPP_ */
