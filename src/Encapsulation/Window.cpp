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
    RAYLIB::InitWindow(width, height, msg.c_str());
    this->setFps();
}

// ------ Getters & setters ------
void rl::Window::setFps(const int fps)
{
    this->_fps = fps;
    RAYLIB::SetTargetFPS(fps);
}

int rl::Window::getFps()
{
    return (this->_fps);
}

int rl::Window::getWidth()
{
    return RAYLIB::GetScreenWidth();
}

int rl::Window::getHeight()
{
    return RAYLIB::GetScreenHeight();
}


// ------ Méthodes ------
void rl::Window::fullscreen()
{
    RAYLIB::ToggleFullscreen();
}

bool rl::Window::loop()
{
    RAYLIB::BeginDrawing();
    RAYLIB::EndDrawing();
    return (!RAYLIB::WindowShouldClose());
}

void rl::Window::clear(RAYLIB::Color color)
{
    RAYLIB::ClearBackground(color);
}

void rl::Window::destroy()
{
    RAYLIB::CloseWindow();
}