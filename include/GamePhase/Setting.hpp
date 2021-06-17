/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Setting
*/

#ifndef SETTING_HPP_
#define SETTING_HPP_

#include "Game.hpp"
#include "Button.hpp"
#include "encapsulation.hpp"
#include "InputButton.hpp"
#include "Server.hpp"

class Setting
{
public:
    Setting();
    ~Setting();
    void check_buttonclick();
    void draw_touch();
    GamePhase settingPhase(GamePhase gamePhase);
    GamePhase launch();
    GamePhase restart();
    void init();
private:
    Button _bUp;
    Button _bDown;
    Button _bUpFram;
    Button _bDownFram;
    Button _bChange;
    Button _bReturn;
    rl::Text _tReturn;
    std::vector<Button> _bInput;
    std::vector<int> _ikey;
    RAYLIB::Texture2D _tbackground;
};

#endif