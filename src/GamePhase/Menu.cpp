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
    this->_bPlay = Button(34, 15, 32, 18);
    this->_bQuit = Button(34, 55, 32, 18);
    this->_tPlay = rl::Text("Play", 43, 17, 70, RAYLIB::LIGHTGRAY);
    this->_tQuit = rl::Text("Quit", 43, 57, 70, RAYLIB::LIGHTGRAY);

    // PlayPhase
    this->_bJoinGame = Button(26.5, 15, 47, 18);
    this->_bCreateGame = Button(26.5, 55, 47, 18);
    this->_tJoinGame = rl::Text("JoinGame", 42, 17, 70, RAYLIB::LIGHTGRAY);
    this->_tCreateGame = rl::Text("CreateGame", 42, 57, 70, RAYLIB::LIGHTGRAY);

    // JoinPhase
    this->_iIp = InputButton(8, 60, 50, 11, 16);
    this->_iPort = InputButton(72, 60, 15, 11, 5);
    this->_iYourName = InputButton(25, 18, 50, 11, 16);
    this->_tYourName = rl::Text("YourName", 41, 5, 70, RAYLIB::LIGHTGRAY);
    this->_tIp = rl::Text("Ip", 31, 46, 70, RAYLIB::LIGHTGRAY);
    this->_tPort = rl::Text("Port", 75, 46, 70, RAYLIB::LIGHTGRAY);
    this->_bJoin = Button(35, 79, 31, 18);
    this->_tJoin = rl::Text("Join", 42, 80, 70, RAYLIB::LIGHTGRAY);

    // CreatePhase
    this->_iServPort = InputButton(42, 37, 15, 11, 5);
    this->_tServPort = rl::Text("Port of your server", 24, 26, 55, RAYLIB::LIGHTGRAY);
    this->_bCreate = Button(35, 79, 31, 18);
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

    this->_bPlay.draw();
    this->_bQuit.draw();
    this->_tPlay.draw();
    this->_tQuit.draw();
    return (gamePhase);
}

GamePhase Menu::playPhase(GamePhase gamePhase)
{
    if (this->_bCreateGame.isClicked())
        this->_phase = CreatePhase;
    if (this->_bJoinGame.isClicked())
        this->_phase = JoinPhase;

    this->_bJoinGame.draw();
    this->_bCreateGame.draw();
    this->_tCreateGame.draw();
    this->_tJoinGame.draw();
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