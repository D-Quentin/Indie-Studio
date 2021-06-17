#ifndef BOMBERMAN_ENTITYOBJECTS_HPP
#define BOMBERMAN_ENTITYOBJECTS_HPP

#include "GameObject.hpp"
#include "Model.hpp"

class EntityObjects : public GameObject {
    public:
        EntityObjects(RAYLIB::Vector2 = {0, 0}, int = -1) {};
        ~EntityObjects() = default;

        int getHealth();
        void takeDamage(int damage) {_health -= damage;};
        bool isAlive() {return (_health > 0) ;};
        void draw();
        float _rota;
        rl::Models _model;

    protected:
        int _health = 100;
        float _scale;
    };


#endif //BOMBERMAN_ENTITYOBJECTS_HPP