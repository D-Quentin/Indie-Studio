#ifndef BOMBERMAN_AI_HPP
#define BOMBERMAN_AI_HPP

#include <utility>
#include "EntityObjects.hpp"

enum Target {IN_RANGE, ABSENT, MOVING, UNDEFINED};

class Ai : public EntityObjects {
public:
    Ai(std::vector<std::vector<char>> map);
    ~Ai() = default;

    Target checkEnemy();
    RAYLIB::Vector2 getEnemyPosition();
    int calculateDistObj(unsigned int axis);
    float Vector2Angle(RAYLIB::Vector2 v1, RAYLIB::Vector2 v2);
    std::vector<RAYLIB::KeyboardKey> getDirections();
    bool isTileValid(RAYLIB::Vector2 tile);
    bool isInMap(RAYLIB::Vector2 tile);
    void getAvailableTiles();
    void setDirections(RAYLIB::Vector2 newPosition);
    void getPriority();
    void attackEnemy();
    void setRandomTarget();
    void moveToNextTile();
    void rotate();

    std::string serialize();
    void deserialize(std::string str);

protected:
    RAYLIB::Vector2 targetPosition;
    Target targetStatus;
    std::vector<RAYLIB::KeyboardKey> directions;
    std::vector<std::vector<char>> map;
    RAYLIB::Vector2 last_pos;
    std::vector<RAYLIB::Vector2> open;
    //std::pair<RAYLIB::Vector2, RAYLIB::Vector2> close;
};


#endif //BOMBERMAN_AI_HPP