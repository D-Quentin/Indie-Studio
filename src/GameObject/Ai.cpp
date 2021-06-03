#include "Ai.hpp"
#include <string>

Ai::Ai()
{
    this->targetStatus = UNDEFINED;
}

Target Ai::checkEnemy()
{
    return ABSENT;
}

void Ai::getPriority() // This function will check if there is an enemy, if he's in range to attack or move to a random point on the map
{
    Target status = checkEnemy();

    if (status == IN_RANGE && this->targetStatus != IN_RANGE)
        attackEnemy();
    else if (status == TOO_FAR && this->targetStatus != TOO_FAR)
        moveToEnemy();
    else if (status == ABSENT && this->targetStatus != ABSENT)
        setRandomTarget();
}

void Ai::moveToEnemy() // This function will move set the target position of the ai to the current position of the enemy
{
    Vector2 enemyPos = getEnemyPosition();

    this->targetPosition = enemyPos;
}

Vector2 Ai::getEnemyPosition() // This function will get the position of the enemy within range
{
    Vector2 pos = {0, 0};

    return pos;
}

void Ai::attackEnemy() // This function will handle the attack system of the ai
{

}

void Ai::setRandomTarget() // This function will set the target position to a random position on the map
{

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