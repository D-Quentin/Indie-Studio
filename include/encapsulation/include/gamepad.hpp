/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** gamepad
*/

#ifndef GAMEPAD_HPP_
#define GAMEPAD_HPP_

#include <raylib.h>
#include <list>
#include <vector>

class Gamepad
{
    public:
        Gamepad(int id) : _id(id) {};
        ~Gamepad() = default;

        std::list<int> getButtonPressed();

        float getAxisLeftX() {return GetGamepadAxisMovement(this->_id, GAMEPAD_AXIS_LEFT_X);};
        float getAxisLeftY() {return GetGamepadAxisMovement(this->_id, GAMEPAD_AXIS_LEFT_Y);};
        std::pair<float, float> getAxisLeft() {return {getAxisLeftX(), getAxisLeftY()}; };

        float getAxisRightX() {return GetGamepadAxisMovement(this->_id, GAMEPAD_AXIS_RIGHT_X);};
        float getAxisRightY() {return GetGamepadAxisMovement(this->_id, GAMEPAD_AXIS_RIGHT_Y);};
        std::pair<float, float> getAxisRight() {return {getAxisRightX(), getAxisRightY()}; };
    private:
        int _id;
};

std::list<int> Gamepad::getButtonPressed()
{
    std::list<int> to_ret;

    for (int i = 1; i <= 17; i++)
        if (IsGamepadButtonDown(this->_id, i))
            to_ret.push_back(i);
    return to_ret;
}

#endif /* !GAMEPAD_HPP_ */
