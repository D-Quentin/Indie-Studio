/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Button
*/

#include "Button.hpp"

Button::Button(int posx, int posy, int width, int height)
{
    this->_posx = posx;
    this->_posy = posy;
    this->_height = height;
    this->_width = width;
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
    if (this->isHover() && RAYLIB::IsMouseButtonDown(RAYLIB::MOUSE_BUTTON_LEFT))
        return (true);
    return (false);
}

bool Button::isClicked()
{
    if (this->isHover() && RAYLIB::IsMouseButtonReleased(RAYLIB::MOUSE_BUTTON_LEFT))
        return (true);
    return (false);
}

void Button::draw()
{
    RAYLIB::DrawRectangle(this->_posx, this->_posy, this->_width, this->_height, RAYLIB::DARKGRAY);
}