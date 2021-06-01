#ifndef BOMBERMAN_AI_HPP
#define BOMBERMAN_AI_HPP

#include "EntityObjects.hpp"

class Ai : public EntityObjects {
    public:
        Ai() = default;
        ~Ai() = default;

        std::string serialize();
        void deserialize(std::string str);
    };


#endif //BOMBERMAN_AI_HPP