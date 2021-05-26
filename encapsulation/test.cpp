/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** test
*/

#include "raylib_encapsulation.hpp"

int main()
{
    window win(450, 900, "salut");
    win.setFps(120);
    Gamepad gmp(0);

    while (win.loop()) {
        if (IsKeyPressed(KEY_R))
            win.fullscreen();
        Text(std::to_string(gmp.getButtonPressed()), win.getWidth() / 2).draw();
        Text(std::to_string(gmp.getAxisLeftX()), win.getWidth() / 2, 1 * 15).draw();
        Text(std::to_string(gmp.getAxisLeftY()), win.getWidth() / 2, 2 * 15).draw();
        Text(std::to_string(gmp.getAxisRightX()), win.getWidth() / 2, 3 * 15).draw();
        Text(std::to_string(gmp.getAxisRightY()), win.getWidth() / 2, 4 * 15).draw();
        win.clear();
    }
    win.destroy();
    return 0;
}
