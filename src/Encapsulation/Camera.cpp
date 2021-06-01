/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Camera
*/

#include "Camera.hpp"
#include <raymath.h>
#include <iostream>

std::pair<float, float> rl::Camera::getpr(float x, float z)
{
    x = std::abs(x);
    z = std::abs(z);
    float globalValue = x + z;
    float xr = x * 100 / globalValue;
    float zr = xr - 100;
    return {std::abs(xr), std::abs(zr)};
}

std::pair<float, float> rl::Camera::assignpr(float value, float x, float y)
{
    return {value * (x / 100), value * (y / 100)};
}

rl::Camera::Camera()
{
    this->setPosition( {0.0f, 0.0f, 0.0f} );
    this->setTarget( {0.0f, 0.0f, 0.0f} );
    _camera.up = {0.0f, 1.0f, 0.0f};
    this->setFOV(45.0);
    this->setProjection(CAMERA_PERSPECTIVE);
    this->setMode(CAMERA_FREE);
}

rl::Camera::Camera(Vector3 pos, CameraMode mode)
{
    this->setPosition(pos);
    this->setTarget( {0.0f, 0.0f, 0.0f} );
    _camera.up = {0.0f, 1.0f, 0.0f};
    this->setFOV(45.0);
    this->setProjection(CAMERA_PERSPECTIVE);
    this->setMode(mode);
}

Vector2 axToMouse(std::pair<float, float> ax)
{
    static double x = GetMousePosition().x;
    static double y = GetMousePosition().y;

    x += ax.first;
    y += ax.second;

    return (Vector2) {x, y};
}

void rl::Camera::updateCamera(std::pair<float, float> gmpAxisLeft, std::pair<float, float> gmpAxisRight)
{
    static const int mouseSensivity = 600;
    static const float minimumY = -65.0f;
    static const float maximumY = 89.0f;
    static Vector2 previousMousePosition = axToMouse(gmpAxisRight);
    static Vector2 angle = {0, 0};

    //udate pos cam from left axis gamepad
        if (gmpAxisLeft != std::make_pair(0.0f, 0.0f)) {
            Vector3 forward = Vector3Subtract(this->getTarget(), this->getPosition());
            forward.y = 0;
            forward = Vector3Normalize(forward);
            Vector3 right = {forward.z * -1.0f, 0, forward.x};
            Vector3 oldPosition = this->getPosition();

            this->setPosition(Vector3Add(this->getPosition(), Vector3Scale(forward, gmpAxisLeft.second * -1 * 0.0075f))); // 0.0075f is the speed bride
            this->setPosition(Vector3Add(this->getPosition(), Vector3Scale(right, gmpAxisLeft.first * 0.0075f)));
        }
        if (gmpAxisRight != std::make_pair(0.0f, 0.0f)) {
            Vector2 mousePosition = axToMouse(gmpAxisRight);
            Vector2 mousePositionDelta = Vector2Subtract(previousMousePosition, mousePosition);
            previousMousePosition = mousePosition;
            float turnRotation = gmpAxisRight.first * GetFrameTime() * this->_speed;
            float tiltRotation = gmpAxisRight.second * GetFrameTime() * this->_speed;

            if (turnRotation != 0)
                angle.x -= turnRotation * DEG2RAD;
            else
                angle.x += mousePositionDelta.x / -mouseSensivity;
            if (tiltRotation)
                angle.y += tiltRotation * DEG2RAD;
            else
                mousePositionDelta.y / -mouseSensivity;

            if (angle.y < minimumY * DEG2RAD)
                angle.y = minimumY * DEG2RAD;
            else if (angle.y > maximumY * DEG2RAD)
                angle.y = maximumY * DEG2RAD;
            Vector3 target = Vector3Transform((Vector3) {0, 0, 1}, MatrixRotateXYZ( (Vector3){-angle.y, -angle.x, 0} ));
            this->setTarget(Vector3Add(this->getPosition(), target));
        }
    //update camera vis;
        // UpdateCamera(&_camera);
}