/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "encapsulation.hpp"

class Button {
   public:
      Button(std::string, int, int, int, int);
      ~Button();
      bool isHover();
      bool isPressed();

   protected:
   private:
      std::string _name;
      int _posx = 0;
      int _posy = 0;
      int _height = 50;
      int _width = 100;
};

#endif /* !BUTTON_HPP_ */
