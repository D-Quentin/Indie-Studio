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
    this->_bPlay = Button(WIN_WIDTH / 2 - 300, 150, 600, 200);
    this->_bQuit = Button(WIN_WIDTH / 2 - 300, 550, 600, 200);
    this->_bJoinGame = Button(WIN_WIDTH / 2 - 450, 150, 900, 200);
    this->_bCreateGame = Button(WIN_WIDTH / 2 - 450, 550, 900, 200);
    this->_tPlay = rl::Text("Play", WIN_WIDTH / 2 - 150, 170, 150);
    this->_tQuit = rl::Text("Quit", WIN_WIDTH / 2 - 150, 570, 150);
    this->_tJoinGame = rl::Text("JoinGame", WIN_WIDTH / 2 - 350, 170, 150);
    this->_tCreateGame = rl::Text("CreateGame", WIN_WIDTH / 2 - 350, 570, 150);
    this->_iIp = InputButton(300, 600, 800, 120, 16);
    this->_iPort = InputButton(1400, 600, 300, 120, 5);
    this->_iYourName = InputButton(450, 120, 800, 120, 16);

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
    this->_tCreateGame.draw(LIGHTGRAY);
    if (this->_bCreateGame.isCliqued())
        this->_phase = CreatePhase;
    if (this->_bJoinGame.isCliqued())
        this->_phase = JoinPhase;
    return (gamePhase);
}

GamePhase Menu::createPhase(GamePhase gamePhase)
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
    return (gamePhase);
}

GamePhase Menu::joinPhase(GamePhase gamePhase)
{
    return (gamePhase);
}
