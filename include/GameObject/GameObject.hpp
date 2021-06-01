/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** GameObject
*/

#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_

#include "IGameObject.hpp"

class GameObject : public IGameObject {
    public:
        GameObject(Vector2 = {0, 0}, int = -1);
        ~GameObject();
        Vector2 getPos();
        int getId();
        void setPos(Vector2);
        void setId(int);

    protected:
        Vector2 _pos;
        int _id;
    private:
};

#endif /* !GAMEOBJECT_HPP_ */
