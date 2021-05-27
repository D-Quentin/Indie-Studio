/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** main
*/

// #include <iostream>

#include "encapsulation.hpp"

int main(void)
{
    rl::Window win("fps boum boum");
    Gamepad gmp(0);

    while(win.loop()) {
        win.clear();
        rl::Text("salopars").draw();
    }
    win.destroy();
    return 0;
}