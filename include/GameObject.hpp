#ifndef BOMBERMAN_GAMEOBJECTS_HPP
#define BOMBERMAN_GAMEOBJECTS_HPP

#include <vector>

namespace game_object {
    class GameObject {
    public:
        GameObject() = default;
        ~GameObject() = default;

        std::vector<double> getPosition();

    protected:
        std::vector<double>_currentPosition;
        // texture
    };
}

#endif //BOMBERMAN_GAMEOBJECTS_HPP