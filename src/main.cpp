/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** main
*/

// #include <iostream>
#include "encapsulation/raylib_encapsulation.hpp"

int main(void)
{
    window win("fps boum boum");
    Gamepad gmp(0);

    while(win.loop()) {
        win.clear();
        Text("salopars").draw();
    }
    win.destroy();
    return 0;
}