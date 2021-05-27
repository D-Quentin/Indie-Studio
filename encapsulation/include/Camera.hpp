/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "raylib.h"

namespace rl {
    class Camera
    {
        public:
            Camera();
            Camera(Vector3, CameraMode);
            ~Camera();

            // Getters & setters
            void setPosition(Vector3);
            void setTarget(Vector3);
            void setFOV(float);
            void setProjection(CameraProjection);
            void setMode(CameraMode);
            Vector3 getPosition(void) const;
            Vector3 getTarget(void) const;
            float getCameraFOV(void) const;
            void updateCamera();

        protected:
        private:
            Camera3D _camera;
            Vector3 _pos;
            Vector3 _target;
            CameraProjection _projection;
            CameraMode _mode;
            float _fov;
    };
};


#endif /* !CAMERA_HPP_ */
