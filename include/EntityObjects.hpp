#ifndef BOMBERMAN_ENTITYOBJECTS_HPP
#define BOMBERMAN_ENTITYOBJECTS_HPP

#include "GameObject.hpp"
#include "misc.hpp"

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
        unsigned int _speed;
        Direction _direction;
        // current weapon
        // view range
    };
}

#endif //BOMBERMAN_ENTITYOBJECTS_HPP