/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** main
*/

// #include <iostream>

#include "encapsulation.hpp"
#include "Game.hpp"

int main(void)
{
    rl::Window win(WIN_WIDTH, WIN_HEIGHT, "Indie Studio");
    Game game;

    win.fullscreen();
    game.launch(win);
    win.destroy();
    return 0;
}