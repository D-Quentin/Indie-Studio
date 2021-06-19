#include "Ai.hpp"
#include <string>
#include <cstdlib>
#include <ctime>

float Ai::Vector2Angle(RAYLIB::Vector2 v1, RAYLIB::Vector2 v2)
{
    float result = atan2f(v2.y - v1.y, v2.x - v1.x) * (180.0f / PI);
    if (result < 0) result += 360.0f;
    return result;
}

Ai::Ai(std::vector<std::vector<char>> map)
{
    static auto globalPlayerModel = rl::Models("assets/character/character.obj");
    static auto __bb = RAYLIB::MeshBoundingBox(globalPlayerModel._model.meshes[0]);
    static float __varForCalculateScale = __bb.min.z - __bb.max.z;
    this->_scale = std::abs(0.3 / __varForCalculateScale);
    this->_model = globalPlayerModel;
    this->map = map;
    this->_rota = 0;
    this->targetStatus = UNDEFINED;
    this->_weapon1 = new Pistol();
    this->targetPosition.x = 0;
    this->targetPosition.y = 0;
    this->close = {{0, 0}, {0, 0}};
}

Target Ai::checkEnemy()
{
    return ABSENT;
}

void Ai::rotate()
{
    float newRota = -Vector2Angle({(float)RAYLIB::GetScreenWidth() / 2, (float)RAYLIB::GetScreenHeight() / 2}, RAYLIB::GetMousePosition());

    if (this->_rota == newRota)
        return;
    this->_rota = newRota;
    this->_change = true;
}

double Ai::calculateDist(RAYLIB::Vector2 pos)
{
    int diff_x = abs(this->targetPosition.x - pos.x);
    int diff_y = abs(this->targetPosition.y - pos.y);

    double res = diff_x + diff_y;
    //double res = sqrt(pow(diff_x, 2) + pow(diff_y, 2));
    printf("Distances: %f\n", res);
    return res;
}

void Ai::moveToNextTile() {
    printf("MOVING TO NEXT TILE\n");
    std::vector<RAYLIB::Vector2> tmp;
    std::vector<RAYLIB::Vector2> open_pos;
    std::vector<float> dist;
    RAYLIB::Vector2 pos;

    this->close.first = this->close.second;
    this->close.second = this->_pos;
    for (int y = -1; y < 2; y++) {
        pos.y = this->_pos.y + y;
        for (int x = -1; x < 2; x++) {
            pos.x = this->_pos.x + x;
            if (this->map[pos.y][pos.x] == ' ' || this->map[pos.y][pos.x] == 'S')
                tmp.push_back(pos);
        }
    }
    printf("Current coordinates: [%f::%f]\n", this->_pos.x, this->_pos.y);
    printf("Target coordinates: [%f::%f]\n", this->targetPosition.x, this->targetPosition.y);
    printf("Banned coordinates: [%f::%f], [%f::%f]\n", this->close.first.x, this->close.first.y, this->close.second.x, this->close.second.y);
    for (unsigned long i = 0; i < tmp.size(); i++)
        printf("Available coordinates [%f::%f]-> [%c]\n", tmp[i].x, tmp[i].y, this->map[tmp[i].y][tmp[i].x]);
    for (unsigned int i = 0; i < tmp.size(); i++)
        if (tmp[i].x != this->close.first.x || tmp[i].y != this->close.first.y || tmp[i].x != this->close.second.x || tmp[i].y != this->close.second.y)
            open_pos.push_back(tmp[i]);
    for (unsigned int i = 0; i < open_pos.size(); i++)
        dist.push_back(calculateDist(open_pos[i]));
    auto min_value = std::min_element(dist.begin(), dist.end());
    setDirections(open_pos[min_value - dist.begin()]);
    setPos(open_pos[min_value - dist.begin()]);
    printf("Next coordinates: [%f::%f]\n", open_pos[min_value - dist.begin()].x, open_pos[min_value - dist.begin()].y);
}

std::vector<RAYLIB::KeyboardKey> Ai::getDirections()
{
    return this->directions;
}

void Ai::setDirections(RAYLIB::Vector2 newPosition)
{
    this->directions.clear();
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

    if (this->targetPosition.x == this->_pos.x && this->targetPosition.y == this->_pos.y)
        this->targetStatus = ABSENT;

    if (status == IN_RANGE && this->targetStatus != IN_RANGE)
        attackEnemy();
    else if (status == TOO_FAR && this->targetStatus != TOO_FAR)
        moveToEnemy();
    else if (status == ABSENT && (this->targetStatus == UNDEFINED || this->targetStatus == ABSENT))
        setRandomTarget();
    moveToNextTile();
}

void Ai::moveToEnemy() // This function will move set the target position of the ai to the current position of the enemy
{
    printf("MOVING TOWARD THE ENEMY\n");
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
    printf("ATTACK\n");
}

void Ai::setRandomTarget() // This function will set the target position to a random position on the map using a* algorithm
{
    int size_x = this->map[0].size();
    int size_y = this->map.size();

    printf("SETTING NEW TARGET\n");
    std::srand(std::time(nullptr));
    while (this->map[this->targetPosition.y][this->targetPosition.x] != ' ' && this->map[this->targetPosition.y][this->targetPosition.x] != 'S') {
        this->targetPosition.x = std::rand() % size_x - 1;
        this->targetPosition.y = std::rand() % size_y - 1;
    }
    printf("New Target coordinates: [%f::%f]\n", this->targetPosition.x, this->targetPosition.y);
    this->targetStatus = RANDOM;
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