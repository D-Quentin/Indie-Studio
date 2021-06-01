#ifndef BOMBERMAN_ENTITYOBJECTS_HPP
#define BOMBERMAN_ENTITYOBJECTS_HPP

#include "GameObject/GameObject.hpp"

class EntityObjects : public GameObject {
    public:
        EntityObjects() = default;
        ~EntityObjects() = default;

        unsigned int getHealth();

    protected:
        unsigned int _health;
    };


#endif //BOMBERMAN_ENTITYOBJECTS_HPP