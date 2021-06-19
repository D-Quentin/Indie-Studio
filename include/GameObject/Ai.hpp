#ifndef BOMBERMAN_AI_HPP
#define BOMBERMAN_AI_HPP

#include <utility>
#include "EntityObjects.hpp"

enum Target {IN_RANGE, TOO_FAR, ABSENT, RANDOM, UNDEFINED};

typedef struct {
    RAYLIB::Vector2 position;
    double h; // distance to objective
    unsigned int g; // distance from start
    double f; // result
} node_t;

class Ai : public EntityObjects {
public:
    Ai(std::vector<std::vector<char>> map);
    ~Ai() = default;

    Target checkEnemy();
    RAYLIB::Vector2 getEnemyPosition();
    double calculateDistObj(RAYLIB::Vector2 pos);
    double calculateDistStart(RAYLIB::Vector2 pos);
    float Vector2Angle(RAYLIB::Vector2 v1, RAYLIB::Vector2 v2);
    std::vector<RAYLIB::KeyboardKey> getDirections();
    node_t createNode(RAYLIB::Vector2 node_pos);
    std::pair<node_t, unsigned int> getSmallestF();
    void getAvailableTiles(RAYLIB::Vector2 pos);
    void getValidChildren(RAYLIB::Vector2 children_pos);
    void setDirections(RAYLIB::Vector2 newPosition);
    void getPriority();
    void moveToEnemy();
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
    std::vector<node_t> close;
    std::vector<node_t> open;
    //std::pair<RAYLIB::Vector2, RAYLIB::Vector2> close;
};


#endif //BOMBERMAN_AI_HPP