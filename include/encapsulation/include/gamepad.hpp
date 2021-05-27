/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** gamepad
*/

#ifndef GAMEPAD_HPP_
#define GAMEPAD_HPP_

#include <raylib.h>

class Gamepad
{
    public:
        Gamepad(int id) : _id(id) {};
        ~Gamepad() = default;

        int getButtonPressed();

        float getAxisLeftX() {return GetGamepadAxisMovement(this->_id, GAMEPAD_AXIS_LEFT_X);};
        float getAxisLeftY() {return GetGamepadAxisMovement(this->_id, GAMEPAD_AXIS_LEFT_Y);};
        std::pair<float, float> getAxisLeft() {return {getAxisLeftX(), getAxisLeftY()}; };

        float getAxisRightX() {return GetGamepadAxisMovement(this->_id, GAMEPAD_AXIS_RIGHT_X);};
        float getAxisRightY() {return GetGamepadAxisMovement(this->_id, GAMEPAD_AXIS_RIGHT_Y);};
        std::pair<float, float> getAxisRight() {return {getAxisRightX(), getAxisRightY()}; };
    private:
        int _id;
};

int Gamepad::getButtonPressed()
{
    // arrow key
    if (IsGamepadButtonDown(this->_id, GAMEPAD_BUTTON_LEFT_FACE_UP))
        return GAMEPAD_BUTTON_LEFT_FACE_UP;
    if (IsGamepadButtonDown(this->_id, GAMEPAD_BUTTON_LEFT_FACE_RIGHT))
        return GAMEPAD_BUTTON_LEFT_FACE_RIGHT;
    if (IsGamepadButtonDown(this->_id, GAMEPAD_BUTTON_LEFT_FACE_DOWN))
        return GAMEPAD_BUTTON_LEFT_FACE_DOWN;
    if (IsGamepadButtonDown(this->_id, GAMEPAD_BUTTON_LEFT_FACE_LEFT))
        return GAMEPAD_BUTTON_LEFT_FACE_LEFT;

    // XBOX: [Y,X,A,B] PS3: [Triangle,Square,Cross,Circle]
    if (IsGamepadButtonDown(this->_id, GAMEPAD_BUTTON_RIGHT_FACE_UP))
        return GAMEPAD_BUTTON_RIGHT_FACE_UP;
    if (IsGamepadButtonDown(this->_id, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
        return GAMEPAD_BUTTON_RIGHT_FACE_RIGHT;
    if (IsGamepadButtonDown(this->_id, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
        return GAMEPAD_BUTTON_RIGHT_FACE_DOWN;
    if (IsGamepadButtonDown(this->_id, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))
        return GAMEPAD_BUTTON_RIGHT_FACE_LEFT;

    //triggers
    if (IsGamepadButtonDown(this->_id, GAMEPAD_BUTTON_LEFT_TRIGGER_1)) // lb
        return GAMEPAD_BUTTON_LEFT_TRIGGER_1;
    if (IsGamepadButtonDown(this->_id, GAMEPAD_BUTTON_LEFT_TRIGGER_2)) //lt
        return GAMEPAD_BUTTON_LEFT_TRIGGER_2;
    if (IsGamepadButtonDown(this->_id, GAMEPAD_BUTTON_RIGHT_TRIGGER_1)) //rb
        return GAMEPAD_BUTTON_RIGHT_TRIGGER_1;
    if (IsGamepadButtonDown(this->_id, GAMEPAD_BUTTON_RIGHT_TRIGGER_2)) // rt
        return GAMEPAD_BUTTON_RIGHT_TRIGGER_2;
    
    //mid button
    if (IsGamepadButtonDown(this->_id, GAMEPAD_BUTTON_MIDDLE_LEFT))// LEFT MID BUTTON
        return GAMEPAD_BUTTON_MIDDLE_LEFT;
    if (IsGamepadButtonDown(this->_id, GAMEPAD_BUTTON_MIDDLE))   // PS Button/XBOX Button
        return GAMEPAD_BUTTON_MIDDLE;
    if (IsGamepadButtonDown(this->_id, GAMEPAD_BUTTON_MIDDLE_RIGHT))   // RIGHT MID BUTTON
        return GAMEPAD_BUTTON_MIDDLE_RIGHT;

    // These are the joystick press in buttons
    if (IsGamepadButtonDown(this->_id, GAMEPAD_BUTTON_LEFT_THUMB))
        return GAMEPAD_BUTTON_LEFT_THUMB;
    if (IsGamepadButtonDown(this->_id, GAMEPAD_BUTTON_RIGHT_THUMB))
        return GAMEPAD_BUTTON_RIGHT_THUMB;
    return 0;
}

#endif /* !GAMEPAD_HPP_ */
