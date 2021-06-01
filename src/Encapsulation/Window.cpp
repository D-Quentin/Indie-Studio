/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Window
*/

#include "Window.hpp"

// ------ Méthodes spéciales ------
rl::Window::Window()
{
    rl::Window(900, 450, "");
}

rl::Window::Window(const std::string windowName)
{
    rl::Window(900, 450, windowName);
}

rl::Window::Window(const int width, const int height)
{
    rl::Window(width, height, "");
}

rl::Window::Window(const int width, const int height, const std::string msg)
{
    InitWindow(width, height, msg.c_str());
    this->setFps();
}

// ------ Getters & setters ------
void rl::Window::setFps(const int fps)
{
    this->_fps = fps;
    SetTargetFPS(fps);
}

int rl::Window::getFps()
{
    return (this->_fps);
}

int rl::Window::getWidth()
{
    return GetScreenWidth();
}

int rl::Window::getHeight()
{
    return GetScreenHeight();
}


// ------ Méthodes ------
void rl::Window::fullscreen()
{
    ToggleFullscreen();
}

bool rl::Window::loop()
{
    BeginDrawing();
    EndDrawing();
    return (!WindowShouldClose());
}

void rl::Window::clear(color col)
{
    int r = 0, g = 0, b = 0, a = 0;
    Color c;

    std::tie(r, g, b, a) = col;
    c.r = (unsigned char)r;
    c.g = (unsigned char)g;
    c.b = (unsigned char)b;
    c.a = (unsigned char)a;
    ClearBackground(c);
}

void rl::Window::destroy()
{
    CloseWindow();
}