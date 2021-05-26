/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include <raylib.h>
#include <string>
#include <tuple>

#define color std::tuple<int,int,int,int>

class Text
{
    public:
        Text(std::string v = "", int posx = 0, int posy = 0, int font_size = 15) : _text(v), _posx(posx), _posy(posy), _font_size(font_size) {};
        ~Text() = default;

        void setText(std::string text) {_text = text;};

        void setPosX(int val) {_posx = val;};
        void setPosY(int val) {_posy = val;};
        void setPos(int x, int y) {setPosX(x); setPosY(y);};

        void setFontSize(int val) {_font_size = val;};

        int getPosX(void) {return _posx;};
        int getPosY(void) {return _posy;};
        std::pair<int, int>getPos() {return {getPosX(), getPosY()};};
        void draw(color col = {0,0,0,255}) {DrawText(_text.c_str(), _posx, _posy, _font_size, (Color) {(unsigned char)std::get<0>(col), (unsigned char)std::get<1>(col), (unsigned char)std::get<2>(col), (unsigned char)std::get<3>(col)});};
    private :
        std::string _text;
        int _posx = 0;
        int _posy = 0;
        int _font_size = 15;
};

#endif /* !TEXT_HPP_ */
