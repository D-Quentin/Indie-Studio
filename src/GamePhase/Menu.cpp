/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Menu
*/

#include "Menu.hpp"
#include "Server.hpp"
#include "Game.hpp"

Menu::Menu()
{
}

Menu::~Menu()
{
}

GamePhase Menu::launch()
{
    this->_phase = Menu::MainPhase;

    // MainPhase
    this->_bPlay = Button("assets/texture/play_button.png", 20, 35, 36.3, 10.37);
    this->_bHtp = Button("assets/texture/button.png", 75, 32, 21.4, 10);
    this->_bSettings = Button("assets/texture/button.png", 75, 17, 21.4, 10);
    this->_bWeapon = Button("assets/texture/button.png", 75, 47, 21.4, 10);
    this->_bQuit = Button("assets/texture/button.png", 75, 62, 21.4, 10);
    this->_tQuit = rl::Text("Quit", 82, 65, 29, RAYLIB::BLACK);
    this->_tSettings = rl::Text("Settings", 80, 20, 29, RAYLIB::BLACK);
    this->_tHtp = rl::Text("How To Play", 77, 35, 29, RAYLIB::BLACK);
    this->_tWeapon = rl::Text("Weapons", 80, 50, 29, RAYLIB::BLACK);
    this->_tbackground = RAYLIB::LoadTexture("assets/texture/background.png");

    // PlayPhase
    this->_bJoinGame = Button("assets/texture/button_second_page.png", 15, 30, 67.68, 17.1);
    this->_bCreateGame = Button("assets/texture/button_second_page.png", 15, 55, 67.65, 17.1);
    this->_bReturn = Button("assets/texture/button.png", 3, 85, 21.4, 10);
    this->_tJoinGame = rl::Text("Join Game", 32, 33, 70, RAYLIB::BLACK);
    this->_tCreateGame = rl::Text("Create Game", 27, 58, 70, RAYLIB::BLACK);
    this->_tReturn = rl::Text("Return", 9, 88, 29, RAYLIB::BLACK);
    this->_tbackground2 = RAYLIB::LoadTexture("assets/texture/background2.png");

    // Settingphase
    this->_bUp = Button("assets/texture/button_second_page.png", 10, 30, 67.68, 17.1);
    this->_bDown = Button("assets/texture/button_second_page.png", 15, 30, 67.68, 17.1);

    // JoinPhase
    this->_iIp = InputButton(8, 60, 50, 11, 16);
    this->_iPort = InputButton(72, 60, 15, 11, 5);
    this->_iYourName = InputButton(25, 18, 50, 11, 16);
    this->_tYourName = rl::Text("YourName", 41, 5, 70, RAYLIB::LIGHTGRAY);
    this->_tIp = rl::Text("Ip", 31, 46, 70, RAYLIB::LIGHTGRAY);
    this->_tPort = rl::Text("Port", 75, 46, 70, RAYLIB::LIGHTGRAY);
    this->_bJoin = Button("", 35, 79, 31, 18);
    this->_tJoin = rl::Text("Join", 42, 80, 70, RAYLIB::LIGHTGRAY);

    // CreatePhase
    this->_iServPort = InputButton(42, 37, 15, 11, 5);
    this->_tServPort = rl::Text("Port of your server", 24, 26, 55, RAYLIB::LIGHTGRAY);
    this->_bCreate = Button("", 35, 79, 31, 18);
    this->_tCreate = rl::Text("Create", 35, 80, 70, RAYLIB::LIGHTGRAY);

    return (this->restart());
}

GamePhase Menu::restart()
{
    GamePhase gamePhase = MenuPhase;

    switch (this->_phase) {
    case Menu::MainPhase:
        gamePhase = this->mainPhase(gamePhase);
        break;
    case Menu::PlayPhase:
        gamePhase = this->playPhase(gamePhase);
        break;
    case Menu::CreatePhase:
        gamePhase = this->createPhase(gamePhase);
        break;
    case Menu::JoinPhase:
        gamePhase = this->joinPhase(gamePhase);
        break;
    case Menu::SettingPhase:
        gamePhase = this->settingPhase(gamePhase);
    
    default:
        break;
    }
    return (gamePhase);
}

GamePhase Menu::mainPhase(GamePhase gamePhase)
{
    if (this->_bQuit.isClicked())
        return (QuitPhase);
    if (this->_bPlay.isClicked()) {
        this->_phase = Menu::PlayPhase;
    }
    if (this->_bSettings.isClicked()) {
        this->_phase = Menu::SettingPhase;
    }
    RAYLIB::DrawTextureEx(this->_tbackground, {0, 0}, 0, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::WHITE);
    this->_bPlay.draw();
    this->_bSettings.draw();
    this->_bHtp.draw();
    this->_bWeapon.draw();
    this->_bQuit.draw();
    this->_tSettings.draw();
    this->_tHtp.draw();
    this->_tWeapon.draw();
    this->_tQuit.draw();
    return (gamePhase);
}

GamePhase Menu::settingPhase(GamePhase gamePhase)
{
    static int i = 0;
    rl::Text sound;
    std::stringstream sstream;

    if (this->_bReturn.isClicked())
        this->_phase = MainPhase;
    if (this->_bUp.isPressed() && i < 100)
        i++;
    if (this->_bDown.isPressed() && i > 0)
        i--;
    sstream << i;
    sound = rl::Text(sstream.str(), 75, 46, 70, RAYLIB::LIGHTGRAY);
    RAYLIB::DrawTextureEx(this->_tbackground, {0, 0}, 0, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::WHITE);
    this->_bReturn.draw();
    this->_tReturn.draw();
    this->_bUp.draw();
    this->_bDown.draw();
    sound.draw();
    return (gamePhase);
}

GamePhase Menu::playPhase(GamePhase gamePhase)
{
    if (this->_bCreateGame.isClicked())
        this->_phase = CreatePhase;
    if (this->_bJoinGame.isClicked())
        this->_phase = JoinPhase;
    if (this->_bReturn.isClicked())
        this->_phase = MainPhase;
    RAYLIB::DrawTextureEx(this->_tbackground, {0, 0}, 0, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::WHITE);
    this->_bJoinGame.draw();
    this->_bCreateGame.draw();
    this->_bReturn.draw();
    this->_tCreateGame.draw();
    this->_tJoinGame.draw();
    this->_tReturn.draw();
    return (gamePhase);
}

GamePhase Menu::createPhase(GamePhase gamePhase)
{
    if (this->_iServPort.isSelected())
        this->_iServPort.writeChar(); // GESTION ERREUR
    if (this->_bCreate.isClicked()) {
        Server::launch(std::atoi(this->_iServPort.getText().c_str()));
        return (LobbyPhase);
    }
    this->_iServPort.draw();
    this->_bCreate.draw();
    this->_tServPort.draw();
    this->_tCreate.draw();
    return (gamePhase);
}

GamePhase Menu::joinPhase(GamePhase gamePhase)
{
    if (this->_iIp.isSelected())
        this->_iIp.writeChar(); // GESTION ERREUR
    if (this->_iPort.isSelected())
        this->_iPort.writeChar(); // GESTION ERREUR
    if (this->_iYourName.isSelected())
        this->_iYourName.writeChar(); // GESTION ERREUR
    if (this->_bJoin.isClicked()) {
        return (LobbyPhase);
    }
    this->_iIp.draw();
    this->_iPort.draw();
    this->_iYourName.draw();
    this->_bJoin.draw();
    this->_tIp.draw();
    this->_tPort.draw();
    this->_tYourName.draw();
    this->_tJoin.draw();

    return (gamePhase);
}

std::string Menu::getIp()
{
    if (this->_iIp.getText() == "")
        return ("127.0.0.1");
    return (this->_iIp.getText());
}

std::string Menu::getPort()
{
    if (this->_phase == JoinPhase)
        return (this->_iPort.getText());
    return (this->_iServPort.getText());
}

std::string Menu::getYourName()
{
    return (this->_iYourName.getText());
}
