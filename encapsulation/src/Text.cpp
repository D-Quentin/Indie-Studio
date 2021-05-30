/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Text
*/

#include "Text.hpp"

rl::Text::Text(std::string str, int posx, int posy, int font_size) : _text(str), _posx(posx), _posy(posy), _font_size(font_size)
{
}

void rl::Text::setText(std::string text)
{
    this->_text = text;
}

void rl::Text::setPosX(int x)
{
    this->_posx = x;
}

void rl::Text::setPosY(int y)
{
    this->_posy = y;
}

void rl::Text::setPos(int x, int y)
{
    this->setPosX(x);
    this->setPosY(y);
}

void rl::Text::setFontSize(int font_size)
{
    this->_font_size = font_size;
}

int rl::Text::getPosX(void)
{
    return (this->_posx);
}

int rl::Text::getPosY(void)
{
    return this->_posy;
}

std::pair<int, int> rl::Text::getPos()
{
    return {getPosX(), getPosY()};
}

void rl::Text::draw(color col)
{
    int r = 0, g = 0, b = 0, a = 0;

    std::tie(r,g,b,a) = col;
    DrawText(this->_text.c_str(), _posx, _posy, _font_size, (Color) {(unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a});
}
