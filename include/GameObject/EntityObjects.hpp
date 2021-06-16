#ifndef BOMBERMAN_ENTITYOBJECTS_HPP
#define BOMBERMAN_ENTITYOBJECTS_HPP

#include "GameObject.hpp"
#include "Model.hpp"

class EntityObjects : public GameObject {
    public:
        EntityObjects(RAYLIB::Vector2 = {0, 0}, int = -1) {};
        ~EntityObjects() = default;

        unsigned int getHealth();
        void draw();
        float _rota;
        rl::Models _model;

    protected:
        unsigned int _health;
        float _scale;
    };


#endif //BOMBERMAN_ENTITYOBJECTS_HPP