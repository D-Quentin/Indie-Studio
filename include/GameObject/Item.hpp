#ifndef BOMBERMAN_ITEM_HPP
#define BOMBERMAN_ITEM_HPP

#include "GameObject.hpp"

namespace game_object {
    class Item : public GameObject {
    public:
        Item() = default;
        ~Item() = default;
    };
}

#endif //BOMBERMAN_ITEM_HPP