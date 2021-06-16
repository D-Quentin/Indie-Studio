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
        JoinPhase,
        SettingPhase
    };
    public:
        Menu();
        ~Menu();
        GamePhase launch();
        GamePhase restart();
        GamePhase mainPhase(GamePhase);
        GamePhase playPhase(GamePhase);
        GamePhase settingPhase(GamePhase);
        GamePhase createPhase(GamePhase);
        GamePhase joinPhase(GamePhase);
        std::string getIp();
        std::string getPort();
        std::string getYourName();
        void check_buttonclick();
        void draw_touch();

    protected:
    private:
        Phase _phase;

        // MainPhase
        Button _bPlay;
        Button _bQuit;
        Button _bWeapon;
        Button _bHtp;
        Button _bSettings;
        rl::Text _tQuit;
        rl::Text _tSettings;
        rl::Text _tHtp;
        rl::Text _tWeapon;
        RAYLIB::Texture2D _tbackground;

        // PlayPhase
        Button _bJoinGame;
        Button _bCreateGame;
        Button _bReturn;
        rl::Text _tJoinGame;
        rl::Text _tCreateGame;
        rl::Text _tReturn;
        RAYLIB::Texture2D _tbackground2;

        // SettingPhase
        Button _bUp;
        Button _bDown;
        std::vector<Button> _bInput;
        std::vector<int> _ikey;

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
