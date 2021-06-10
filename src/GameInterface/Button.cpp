/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Button
*/

#include "Button.hpp"

Button::Button(float posx, float posy, float width, float height)
{
    int WIN_HEIGHT = RAYLIB::GetScreenHeight();
    int WIN_WIDTH = RAYLIB::GetScreenWidth();

    this->_posx = (int)(posx * WIN_WIDTH) / 100;
    this->_posy = (int)(posy * WIN_HEIGHT) / 100;
    this->_height = (int)(height * WIN_HEIGHT) / 100;
    this->_width = (int)(width * WIN_WIDTH) / 100;
}

Button::~Button()
{
}

bool Button::isHover()
{
    RAYLIB::Vector2 pos = RAYLIB::GetMousePosition();

    if (pos.x >= this->_posx && pos.x <= this->_posx + this->_width &&
        pos.y >= this->_posy && pos.y <= this->_posy + this->_height)
        return (true);
    return (false);
}

bool Button::isPressed()
{
    if (this->isHover() && RAYLIB::IsMouseButtonDown(RAYLIB::MOUSE_LEFT_BUTTON))
        return (true);
    return (false);
}

bool Button::isClicked()
{
    if (this->isHover() && RAYLIB::IsMouseButtonReleased(RAYLIB::MOUSE_LEFT_BUTTON))
        return (true);
    return (false);
}

void Button::draw()
{
    RAYLIB::DrawRectangle(this->_posx, this->_posy, this->_width, this->_height, RAYLIB::DARKGRAY);
}