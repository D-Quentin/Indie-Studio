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
#include "IGamePhase.hpp"
#include "encapsulation.hpp"
#include "Player.hpp"
#include <map>
#include <memory>

class Lobby : public IGamePhase {
    enum Phase {
        MainPhase,
        JoinPhase
    };
    public:
        Lobby();
        ~Lobby();
        GamePhase launch();
        GamePhase restart();
        GamePhase mainPhase(GamePhase);
        GamePhase joinPhase(GamePhase);

    protected:
    private:
        Phase _phase;
        std::map<int, GameObject *> _obj;
        int _player;
        int _readyPlayer;

        Button _bReady;
        rl::Text _tReady;
};

#endif /* !LOBBY_HPP_ */
