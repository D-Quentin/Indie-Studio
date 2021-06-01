/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include "IGamePhase.hpp"
#include "Button.hpp"
#include "encapsulation.hpp"
#include "InputButton.hpp"

class Menu : public IGamePhase {
    enum Phase {
        MainPhase,
        PlayPhase,
        CreatePhase,
        JoinPhase
    };
    public:
        Menu();
        ~Menu();
        GamePhase launch();
        GamePhase restart();
        GamePhase mainPhase(GamePhase);
        GamePhase playPhase(GamePhase);
        GamePhase createPhase(GamePhase);
        GamePhase joinPhase(GamePhase);

    protected:
    private:
        Phase _phase;
        Button _bPlay;
        Button _bQuit;
        Button _bJoinGame;
        Button _bCreateGame;
        rl::Text _tPlay;
        rl::Text _tQuit;
        rl::Text _tJoinGame;
        rl::Text _tCreateGame;
        InputButton _iIp;
        InputButton _iPort;
        InputButton _iYourName;
};

#endif /* !MENU_HPP_ */
