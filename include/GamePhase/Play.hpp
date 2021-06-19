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
#include "PowerUp.hpp"

#define GROUNDCOLOR {119,136,153, 255}
#define SPAWNCOLOR {233,150,122, 255}
#define ITEMCOLOR {42, 157, 244, 255}

class Play {
    enum Phase {
        MainPhase,
        JoinPhase
    };
    enum EnumItems {
    ITSpeed = 0,
    ITHealth,
    ITRifle,
    ITSnip
    };
    public:
        const std::map<EnumItems, game_object::Item*> enumToItem = {
            {ITSpeed, (game_object::Item*) new Speed},
            {ITHealth, (game_object::Item*) new Dash},
            {ITRifle, (game_object::Item*) new Rifle},
            {ITSnip, (game_object::Item*)new  Snip}
        };
        Play();
        ~Play();
        GamePhase launch(Client *&, Lobby &);
        GamePhase restart(Client *&, Lobby &);
        GamePhase mainPhase(GamePhase, Client *&);
        GamePhase joinPhase(GamePhase, Client *&, Lobby &);
        void placeItems(std::list<std::pair<float, float>>);

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
        std::list<std::pair<float, float>> _spawns;
        std::list<game_object::Item*> _items;

        rl::Text _tHp;
};

#endif /* !PLAY_HPP_ */
