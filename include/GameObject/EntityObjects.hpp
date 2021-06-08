#ifndef BOMBERMAN_ENTITYOBJECTS_HPP
#define BOMBERMAN_ENTITYOBJECTS_HPP

#include "GameObject.hpp"

class EntityObjects : public GameObject {
    public:
        EntityObjects(RAYLIB::Vector2 = {0, 0}, int = -1) {};
        ~EntityObjects() = default;

        unsigned int getHealth();

    protected:
        unsigned int _health;
    };


#endif //BOMBERMAN_ENTITYOBJECTS_HPP