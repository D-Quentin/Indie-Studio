#ifndef BOMBERMAN_AI_HPP
#define BOMBERMAN_AI_HPP

#include "EntityObjects.hpp"

enum Target {IN_RANGE, TOO_FAR, ABSENT, UNDEFINED};

class Ai : public EntityObjects {
public:
    Ai();
    ~Ai() = default;


    Target checkEnemy();
    void getPriority();
    void moveToEnemy();
    Vector2 getEnemyPosition();
    void attackEnemy();
    void setRandomTarget();
    std::string serialize();
    void deserialize(std::string str);

protected:
    Vector2 targetPosition;
    Target targetStatus;
    };


#endif //BOMBERMAN_AI_HPP