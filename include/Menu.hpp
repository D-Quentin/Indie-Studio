/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include "Game.hpp"
#include "Button.hpp"
#include "encapsulation.hpp"
#include "InputButton.hpp"
#include "Server.hpp"

class Menu {
    enum Phase {
        MainPhase,
        PlayPhase,
        CreatePhase,
        JoinPhase
    };
    public:
        Menu();
        ~Menu();
        GamePhase launch(Server *);
        GamePhase restart(Server *);
        GamePhase mainPhase(GamePhase);
        GamePhase playPhase(GamePhase);
        GamePhase createPhase(GamePhase, Server *);
        GamePhase joinPhase(GamePhase);
        std::string getIp();
        std::string getPort();
        std::string getYourName();

    protected:
    private:
        Phase _phase;
        Server *_server;

        // MainPhase
        Button _bPlay;
        Button _bQuit;
        rl::Text _tPlay;
        rl::Text _tQuit;

        // PlayPhase
        Button _bJoinGame;
        Button _bCreateGame;
        rl::Text _tJoinGame;
        rl::Text _tCreateGame;

        // JoinPhase
        InputButton _iIp;
        InputButton _iPort;
        InputButton _iYourName;
        rl::Text _tYourName;
        rl::Text _tIp;
        rl::Text _tPort;
        Button _bJoin;
        rl::Text _tJoin;

        // CreatePhase
        InputButton _iServPort;
        rl::Text _tServPort;
        rl::Text _tCreate;
        Button _bCreate;
};

#endif /* !MENU_HPP_ */
