/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** model
*/

#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "include.hpp"

namespace rl {
    class Models
    {
        public:
            Models(RAYLIB::Mesh, RAYLIB::Texture2D);
            ~Models() = default;

        private:
            void draw();
            RAYLIB::Model _model;
            int _height;
            int _width;
    };
};

#endif /* !MODEL_HPP_ */
