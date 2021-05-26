/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** window
*/

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <tuple>
#include <raylib.h>
#include <iostream>

#define color std::tuple<int,int,int,int>

class window 
{
    public:
        window();
        window(const std::string windowName);
        window(const int width, const int height);
        window(const int width, const int height, const std::string windowName);
        ~window() = default;

        void fullscreen();

        bool loop();
        void setFps(const int = 60);
        int getFps() {return _fps;};;

        int getWidth() {return GetScreenWidth();};;
        int getHeight() {return GetScreenHeight();};

        void clear(color = {255, 0, 0, 255});

        void destroy();

    private:
        int _fps = 60;
};

window::window()
{
    window(900, 450, "");
}

window::window(const std::string windowName)
{
    window(900, 450, windowName);
}

window::window(const int width, const int height)
{
    window(width, height, "");
}

window::window(const int width, const int height, const std::string msg)
{
    InitWindow(width, height, msg.c_str());
    setFps();
}

void window::fullscreen()
{
    ToggleFullscreen();
}

bool window::loop()
{
    BeginDrawing();
    EndDrawing();
    return !WindowShouldClose();
}

void window::setFps(const int fps)
{
    SetTargetFPS(fps);
    _fps = fps;
}

void window::clear(color col)
{
    ClearBackground( (Color) {(unsigned char)std::get<0>(col), (unsigned char)std::get<1>(col), (unsigned char)std::get<2>(col)} );
}

void window::destroy()
{
    CloseWindow();
}

#endif