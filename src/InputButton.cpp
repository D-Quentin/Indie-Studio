/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** InputButton
*/

#include "InputButton.hpp"

InputButton::InputButton(int posx, int posy, int width, int height, int maxLen)
{
    this->_posx = posx;
    this->_posy = posy;
    this->_height = height;
    this->_width = width;
    this->_maxLen = maxLen;
    this->_selected = false;
    this->_button = Button(posx, posy, width, height);
    this->_color = Fade(RAYLIB::ORANGE, 0.6);
    this->_printText = rl::Text("", this->_posx + this->_height * 0.2, this->_posy + this->_height * 0.05, this->_height - this->_height * 0.2, RAYLIB::LIGHTGRAY);
}

InputButton::~InputButton()
{
}

bool InputButton::isSelected()
{
    if (this->_button.isClicked()) {
        this->_selected = true;
        this->_color = Fade(RAYLIB::ORANGE, 1);
    }
    if (RAYLIB::IsMouseButtonDown(RAYLIB::MOUSE_BUTTON_LEFT) && !this->_button.isHover()) {
        this->_selected = false;
        this->_color = Fade(RAYLIB::ORANGE, 0.6);
    }
    return (this->_selected);
}

void InputButton::writeChar()
{
    int key = RAYLIB::GetCharPressed();

    while (key > 0) {
        if ((key >= 32) && (key <= 125) && (this->_text.size() < this->_maxLen))
            this->_text += (char)key;
        key = RAYLIB::GetCharPressed();
    }
    if (RAYLIB::IsKeyPressed(RAYLIB::KEY_BACKSPACE) && this->_text.size() > 0)
        this->_text.pop_back();
    this->_printText.setText(this->_text);
}

void InputButton::draw()
{
    RAYLIB::DrawRectangle(this->_posx, this->_posy, this->_width, this->_height, this->_color);
    RAYLIB::DrawRectangle(this->_posx + this->_height * 0.05, this->_posy + this->_height * 0.05, this->_width - this->_height * 0.1, this->_height - this->_height * 0.1, RAYLIB::DARKGRAY);
    this->_printText.draw();
}

std::string InputButton::getText()
{
    return (this->_text);
}