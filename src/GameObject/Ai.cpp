#include "Ai.hpp"
#include <string>
#include <stdlib.h>
#include <time.h>

Ai::Ai(std::vector<std::vector<char>> map)
{
    this->map = map;
    this->targetStatus = UNDEFINED;
}

Target Ai::checkEnemy()
{
    return ABSENT;
}

double Ai::calculateDist(RAYLIB::Vector2 pos)
{
    int diff_x = this->_pos.x - pos.x;
    int diff_y = this->_pos.y - pos.y;

    return sqrt(diff_x * diff_x + diff_y * diff_y);
}

void Ai::moveToNextTile()
{
    std::vector<RAYLIB::Vector2> open;
    std::vector<float> dist;
    RAYLIB::Vector2 pos;

    this->close.push_back(this->_pos);
    for (int y = -1; y < 2; y++) {
        pos.y = this->_pos.y + y;
        for (int x = -1; x < 2; x++) {
            pos.x = this->_pos.x + x;
            if (this->map[pos.y][pos.x] == ' ' || this-> map[pos.y][pos.x] == 'S')
                open.push_back(pos);
        }
    }
    for (unsigned int i = 0; i < open.size(); i++)
        for (unsigned int j = 0; j < this->close.size(); j++)
            if (open[i].x == this->close[j].x && open[i].y == this->close[j].y) {
                open.erase(open.begin() + i);
                i = 0;
            }
    for (unsigned int i = 0; i < open.size(); i++)
        dist.push_back(calculateDist(open[i]));
    auto min_value = std::min_element(dist.begin(), dist.end());
    setDirections(open[min_value - dist.begin()]);
    setPos(open[min_value - dist.begin()]);
}

std::vector<RAYLIB::KeyboardKey> Ai::getDirections()
{
    return this->directions;
}

void Ai::setDirections(RAYLIB::Vector2 newPosition)
{
    if (newPosition.x < this->_pos.x)
        this->directions.push_back(RAYLIB::KEY_A);
    else if (newPosition.x > this->_pos.x)
        this->directions.push_back(RAYLIB::KEY_D);
    if (newPosition.y < this->_pos.y)
        this->directions.push_back(RAYLIB::KEY_S);
    else if (newPosition.y > this->_pos.y)
        this->directions.push_back(RAYLIB::KEY_W);
}

void Ai::getPriority() // This function will check if there is an enemy, if he's in range to attack or move to a random point on the map
{
    Target status = checkEnemy();
    std::pair<int, int> target_coordinates;

    if (status == IN_RANGE && this->targetStatus != IN_RANGE)
        attackEnemy();
    else if (status == TOO_FAR && this->targetStatus != TOO_FAR)
        moveToEnemy();
    else if (status == ABSENT && this->targetStatus != ABSENT)
        setRandomTarget();
    else if (status == ABSENT && this->targetStatus == ABSENT)
        moveToNextTile();
}

void Ai::moveToEnemy() // This function will move set the target position of the ai to the current position of the enemy
{
    RAYLIB::Vector2 enemyPos = getEnemyPosition();

    this->targetPosition = enemyPos;
}

RAYLIB::Vector2 Ai::getEnemyPosition() // This function will get the position of the enemy within range
{
    RAYLIB::Vector2 pos = {0, 0};

    return pos;
}

void Ai::attackEnemy() // This function will handle the attack system of the ai
{

}

void Ai::setRandomTarget() // This function will set the target position to a random position on the map using a* algorithm
{
    int size_x = this->map[0].size();
    int size_y = this->map.size();

    srand(time(NULL));
    while (map[this->targetPosition.x][this->targetPosition.y] != ' ' || map[this->targetPosition.x][this->targetPosition.y] != 'S') {
        this->targetPosition.x = rand() % size_x;
        this->targetPosition.y = rand() % size_y;
    }
}

std::string Ai::serialize()
{
    std::string str;

    str += "AI;ID:" + std::to_string(this->_id);
    str += ";X:" + std::to_string(this->_pos.x);
    str += ";Y:" + std::to_string(this->_pos.y);

    return (str += "\n");
}

void Ai::deserialize(std::string str)
{
    int pos = 0;

    pos = str.find("X:");
    this->_pos.x = std::atoi(str.substr((pos + 2), str.find(";", pos) - pos).c_str());
    pos = str.find("Y:");
    this->_pos.y = std::atoi(str.substr((pos + 2), str.find(";", pos) - pos).c_str());
}