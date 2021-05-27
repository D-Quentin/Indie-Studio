#ifndef BOMBERMAN_ENTITYOBJECTS_HPP
#define BOMBERMAN_ENTITYOBJECTS_HPP

#include "GameObject.hpp"

namespace game_object {
    class EntityObjects : public GameObject {
    public:
        EntityObjects() = default;
        ~EntityObjects() = default;

        void attack();
        void move();
        void pickObject();
        void setPosition(std::vector<double>newPosition);

    protected:
        unsigned int _health;
        // current weapon
        // view range
    };
}

#endif //BOMBERMAN_ENTITYOBJECTS_HPP