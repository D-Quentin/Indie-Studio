/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Setting
*/

#include "Setting.hpp"

Setting::Setting()
{
}

Setting::~Setting()
{
}

GamePhase Setting::launch()
{
    init();
    return (this->restart());
}

GamePhase Setting::restart()
{
    GamePhase gamePhase = SettingPhase;

    return (settingPhase(SettingPhase));
}

void Setting::init()
{
    this->_bUp = Button("../../../Documents/indi.png", 30, 35, 9.2, 9);
    this->_bDown = Button("../../../Documents/indi.png", 10, 35, 9.2, 9);
    this->_bUpFram = Button("../../../Documents/indi.png", 30, 60, 9.2, 9);
    this->_bDownFram = Button("../../../Documents/indi.png", 10, 60, 9.2, 9);
    for (int i = 0, u = 60, a = 30; i != 6; i++, u += 15) {
        this->_bInput.push_back(Button("../../../Documents/indi.png", u, a, 9.2, 9));
        if (u == 75) {
            u = 45;
            a += 10;
        }
    }
    this->_ikey = {'z', 's', 'q', 'd', 'e', 'i'};
    this->_bChange = Button("assets/texture/button.png", 3, 85, 21.4, 10);
    this->_bReturn = Button("assets/texture/button.png", 3, 85, 21.4, 10);
    this->_tReturn = rl::Text("Return", 9, 88, 29, RAYLIB::BLACK);
    this->_tbackground = RAYLIB::LoadTexture("assets/texture/background.png");
}

void Setting::check_buttonclick()
{
    static int a = 0;
    int b = 0;

    for (int i = 0; i != 6; i++)
        if (this->_bInput[i].isClicked())
            a = i * -1;
    if (a > 0)
        return;
    b = RAYLIB::GetCharPressed();
    if (b <= 0)
        return;
    this->_ikey[a *-1] = b;
    a = 1;
}

void Setting::draw_touch()
{
    rl::Text sound;
    char c = 0;
    std::string str;

    for (int i = 0, u = 60, a = 30; i != 6; i++, u += 15) {
        c = this->_ikey[i];
        if (c == ' ') {
            str = "SPACE";
            sound = rl::Text(str, u+2, a+2, 20, RAYLIB::LIGHTGRAY);
        }
        else {
            str.push_back(c);
            sound = rl::Text(str, u+4, a, 40, RAYLIB::LIGHTGRAY);
        }
        sound.draw();
        str = "";
        if (u == 75) {
            u = 45;
            a += 10;
        }
    }
}

static float check_dist(int nb)
{
    if (nb >= 100)
        return (2.8);
    if (nb >= 10)
        return (1.2);
    return (0);
}

GamePhase Setting::settingPhase(GamePhase gamePhase)
{
    static int i = 0;
    static int f = 60;
    rl::Text sound;
    rl::Text fram;
    int select = 0;

    if (this->_bReturn.isClicked())
        return (GamePhase::MenuPhase);
    if (this->_bUp.isPressed() && i < 100)
        i++;
    if (this->_bDown.isPressed() && i > 0)
        i--;
    if (this->_bUpFram.isPressed() && f < 100)
        f++;
    if (this->_bDownFram.isPressed() && f > 10)
        f--;
    check_buttonclick();
    sound = rl::Text(std::to_string(i), 23 - check_dist(i), 34, 70, RAYLIB::LIGHTGRAY);
    fram = rl::Text(std::to_string(f), 23 - check_dist(f), 58, 70, RAYLIB::LIGHTGRAY);
    RAYLIB::DrawTextureEx(this->_tbackground, {0, 0}, 0, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::WHITE);
    for (int u = 0; u != 6; u++)
        this->_bInput[u].draw();
    this->_bChange.draw();
    this->_bReturn.draw();
    this->_tReturn.draw();
    this->_bUp.draw();
    this->_bDown.draw();
    this->_bUpFram.draw();
    this->_bDownFram.draw();
    sound.draw();
    fram.draw();
    sound = rl::Text("Volume", 17, 25, 50, RAYLIB::LIGHTGRAY);
    fram = rl::Text("Framerate", 14, 48, 50, RAYLIB::LIGHTGRAY);
    sound.draw();
    fram.draw();
    draw_touch();
    return (gamePhase);
}

