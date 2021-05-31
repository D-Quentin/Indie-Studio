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
    Vector2 pos = GetMousePosition();

    if (pos.x >= this->_posx && pos.x <= this->_posx + this->_width &&
        pos.y >= this->_posy && pos.y <= this->_posy + this->_height)
        return (true);
    return (false);
}

bool Button::isPressed()
{
    if (this->isHover() && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        return (true);
    return (false);
}

bool Button::isCliqued()
{
    if (this->isHover() && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        return (true);
    return (false);
}

void Button::draw()
{
    DrawRectangle(this->_posx, this->_posy, this->_width, this->_height, DARKGRAY);
}