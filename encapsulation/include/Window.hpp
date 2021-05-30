/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** window
*/

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "include.hpp"

namespace rl {

    class Window 
    {
        public:
            // Spéciales
            Window();
            Window(const std::string);
            Window(const int, const int);
            Window(const int, const int, const std::string);
            ~Window() = default;

            // Méthodes
            void fullscreen(void);
            bool loop(void);
            void clear(color = {0, 0, 0, 255});
            void destroy(void);

            // Getters & setters
            void setFps(const int = 60);
            int getFps(void);
            int getWidth(void);
            int getHeight(void);

        private:
            int _fps = 60;
    };
}

#endif