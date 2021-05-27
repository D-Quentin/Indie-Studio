/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Camera
*/

#include "Camera.hpp"

rl::Camera::Camera()
{
    Camera3D camera = {0};

    this->_camera = camera;
    this->setPosition( {0.0f, 0.0f, 0.0f} );
    this->setTarget( {0.0f, 0.0f, 0.0f} );
    this->setFOV(45.0);
    this->setProjection(CAMERA_PERSPECTIVE);
    this->setMode(CAMERA_FREE);
}

rl::Camera::Camera(Vector3 pos, CameraMode mode = CAMERA_FREE)
{
    Camera3D camera = {0};

    this->setPosition(pos);
    this->setTarget( {0.0f, 0.0f, 0.0f} );
    this->setFOV(45.0);
    this->setProjection(CAMERA_PERSPECTIVE);
    this->setMode(mode);
}

void rl::Camera::setPosition(Vector3 vector)
{
    this->_pos = vector;
    this->_camera.position = vector;
}

void rl::Camera::setTarget(Vector3 vector)
{
    this->_target = vector;
    this->_camera.target = vector;
}

void rl::Camera::setFOV(float fov)
{
    this->_fov = fov;
    this->_camera.fovy = fov;
}

void rl::Camera::setProjection(CameraProjection projection)
{
    this->_projection = projection;
    this->_camera.projection = projection;
}

void rl::Camera::setMode(CameraMode mode)
{
    this->_mode = mode;
    SetCameraMode(this->_camera, mode);
}

Vector3 rl::Camera::getPosition(void) const
{
    return this->_pos;
}

Vector3 rl::Camera::getTarget(void) const
{
    return this->_target;
}

float rl::Camera::getCameraFOV(void) const
{
    return this->_fov;
}

void rl::Camera::updateCamera()
{
    UpdateCamera(&this->_camera);
}

rl::Camera::~Camera()
{
}