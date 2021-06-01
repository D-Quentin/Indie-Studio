/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Menu
*/

#include "Menu.hpp"

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
    this->_bPlay = Button(WIN_WIDTH / 2 - 300, 150, 600, 200);
    this->_bQuit = Button(WIN_WIDTH / 2 - 300, 550, 600, 200);
    this->_tPlay = rl::Text("Play", WIN_WIDTH / 2 - 150, 170, 150);
    this->_tQuit = rl::Text("Quit", WIN_WIDTH / 2 - 150, 570, 150);

    // PlayPhase
    this->_bJoinGame = Button(WIN_WIDTH / 2 - 450, 150, 900, 200);
    this->_bCreateGame = Button(WIN_WIDTH / 2 - 450, 550, 900, 200);
    this->_tJoinGame = rl::Text("JoinGame", WIN_WIDTH / 2 - 350, 170, 150);
    this->_tCreateGame = rl::Text("CreateGame", WIN_WIDTH / 2 - 350, 570, 150);

    // JoinPhase
    this->_iIp = InputButton(150, 650, 950, 120, 16);
    this->_iPort = InputButton(1400, 650, 300, 120, 5);
    this->_iYourName = InputButton(WIN_WIDTH / 2 - 475, 200, 950, 120, 16);
    this->_tYourName = rl::Text("YourName", WIN_WIDTH / 2 - 350, 50, 150);
    this->_tIp = rl::Text("Ip", 600, 500, 150);
    this->_tPort = rl::Text("Port", 1450, 500, 150);
    this->_bJoin = Button(WIN_WIDTH / 2 - 300, 850, 600, 200);
    this->_tJoin = rl::Text("Join", WIN_WIDTH / 2 - 150, 870, 150);

    // CreatePhase
    this->_iServPort = InputButton(WIN_WIDTH / 2 - 150, 400, 300, 120, 5);
    this->_tServPort = rl::Text("Port of your server", WIN_WIDTH / 2 - 500, 280, 100);
    this->_bCreate = Button(WIN_WIDTH / 2 - 300, 850, 600, 200);
    this->_tCreate = rl::Text("Create", WIN_WIDTH / 2 - 300, 870, 150);

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
    this->_bPlay.draw();
    this->_bQuit.draw();
    this->_tPlay.draw(LIGHTGRAY);
    this->_tQuit.draw(LIGHTGRAY);
    if (this->_bQuit.isCliqued())
        return (QuitPhase);
    if (this->_bPlay.isCliqued()) {
        this->_phase = Menu::PlayPhase;
    }
    return (gamePhase);
}

GamePhase Menu::playPhase(GamePhase gamePhase)
{
    this->_bJoinGame.draw();
    this->_bCreateGame.draw();
    this->_tCreateGame.draw(LIGHTGRAY);
    this->_tJoinGame.draw(LIGHTGRAY);
    if (this->_bCreateGame.isCliqued())
        this->_phase = CreatePhase;
    if (this->_bJoinGame.isCliqued())
        this->_phase = JoinPhase;
    return (gamePhase);
}

GamePhase Menu::createPhase(GamePhase gamePhase)
{
    if (this->_iServPort.isSelected())
        this->_iServPort.writeChar();
    this->_iServPort.draw();
    this->_bCreate.draw();
    this->_tServPort.draw(LIGHTGRAY);
    this->_tCreate.draw(LIGHTGRAY);

    return (gamePhase);
}

GamePhase Menu::joinPhase(GamePhase gamePhase)
{
    if (this->_iIp.isSelected())
        this->_iIp.writeChar();
    if (this->_iPort.isSelected())
        this->_iPort.writeChar();
    if (this->_iYourName.isSelected())
        this->_iYourName.writeChar();
    this->_iIp.draw();
    this->_iPort.draw();
    this->_iYourName.draw();
    this->_bJoin.draw();
    this->_tIp.draw(LIGHTGRAY);
    this->_tPort.draw(LIGHTGRAY);
    this->_tYourName.draw(LIGHTGRAY);
    this->_tJoin.draw(LIGHTGRAY);
    return (gamePhase);
}

std::string Menu::getIp()
{
    return (this->_iIp.getText());
}

std::string Menu::getPort()
{
    return (this->_iPort.getText());
}

std::string Menu::getYourName()
{
    return (this->_iYourName.getText());
}
