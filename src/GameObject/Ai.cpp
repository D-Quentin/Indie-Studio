#include "Ai.hpp"
#include <string>
#include <cstdlib>
#include <ctime>

bool compareVector(RAYLIB::Vector2 first_vector, RAYLIB::Vector2 second_vector)
{
    if (first_vector.x == second_vector.x && first_vector.y == second_vector.y)
        return true;
    return false;
}

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

double Ai::calculateDistObj(RAYLIB::Vector2 pos)
{
    int diff_x = this->targetPosition.x - pos.x;
    int diff_y = this->targetPosition.y - pos.y;

    return sqrt(pow(diff_x, 2) + pow(diff_y, 2));
}

double Ai::calculateDistStart(RAYLIB::Vector2 pos)
{
    int diff_x = this->close[0].position.x - pos.x;
    int diff_y = this->close[0].position.y - pos.y;

    return sqrt(pow(diff_x, 2) + pow(diff_y, 2));
}

node_t Ai::createNode(RAYLIB::Vector2 node_pos)
{
    node_t node;

    node.position = node_pos;
    node.h = calculateDistObj(node_pos);
    node.g = calculateDistStart(node_pos);
    node.f = node.h + node.g;

    return node;
}

void Ai::getValidChildren(RAYLIB::Vector2 children_pos) {
    node_t node;

    for (unsigned int i = 0; i < this->close.size(); i++) {
        if (compareVector(children_pos, this->close[i].position))
            return;
    }
    node = createNode(children_pos);
    for (unsigned int i = 0; i < this->open.size(); i++)
        if (compareVector(node.position, this->open[i].position))
            if (node.g > this->open[i].g)
                return;
    this->open.push_back(node);
}

void Ai::getAvailableTiles(RAYLIB::Vector2 pos)
{
    std::vector<RAYLIB::Vector2> children;

    if (this->map[pos.y - 1][pos.x - 1] == ' ' || this->map[pos.y - 1][pos.x - 1] == 'S')
        children.push_back({pos.y - 1, pos.x - 1});
    if (this->map[pos.y - 1][pos.x] == ' ' || this->map[pos.y - 1][pos.x] == 'S')
        children.push_back({pos.y - 1, pos.x});
    if (this->map[pos.y - 1][pos.x + 1] == ' ' || this->map[pos.y - 1][pos.x + 1] == 'S')
        children.push_back({pos.y - 1, pos.x + 1});
    if (this->map[pos.y][pos.x - 1] == ' ' || this->map[pos.y][pos.x - 1] == 'S')
        children.push_back({pos.y, pos.x - 1});
    if (this->map[pos.y][pos.x + 1] == ' ' || this->map[pos.y][pos.x + 1] == 'S')
        children.push_back({pos.y - 1, pos.x + 1});
    if (this->map[pos.y + 1][pos.x - 1] == ' ' || this->map[pos.y - 1][pos.x - 1] == 'S')
        children.push_back({pos.y + 1, pos.x - 1});
    if (this->map[pos.y + 1][pos.x] == ' ' || this->map[pos.y - 1][pos.x] == 'S')
        children.push_back({pos.y + 1, pos.x});
    if (this->map[pos.y + 1][pos.x + 1] == ' ' || this->map[pos.y - 1][pos.x + 1] == 'S')
        children.push_back({pos.y + 1, pos.x + 1});
    for (unsigned int i = 0; i < children.size(); i++)
        getValidChildren(children[i]);
}

std::pair<node_t, unsigned int> Ai::getSmallestF()
{
    std::pair<node_t, unsigned int> tmp;

    tmp.first = this->open[0];
    tmp.second = 0;
    for (unsigned int i = 0; i < this->open.size(); i++)
        if (this->open[i].f < tmp.first.f) {
            tmp.first = this->open[i];
            tmp.second = i;
        }
    return tmp;
}


void Ai::moveToNextTile() {
    //std::vector<RAYLIB::Vector2> tmp;
    std::pair<node_t, unsigned int> tmp;
    RAYLIB::Vector2 current_pos = this->_pos;
    //std::vector<float> dist;
    //RAYLIB::Vector2 pos;

    //this->close.first = this->close.second;
    //this->close.second = this->_pos;
    //for (int y = -1; y < 2; y++) {
    //    pos.y = this->_pos.y + y;
    //    for (int x = -1; x < 2; x++) {
    //        pos.x = this->_pos.x + x;
    //        if (this->map[pos.y][pos.x] == ' ' || this->map[pos.y][pos.x] == 'S')
    //            tmp.push_back(pos);
    //    }
    //}
    //printf("Current coordinates: [%f::%f]\n", this->_pos.x, this->_pos.y);
    //printf("Target coordinates: [%f::%f]\n", this->targetPosition.x, this->targetPosition.y);
    //printf("Banned coordinates: [%f::%f], [%f::%f]\n", this->close.first.x, this->close.first.y, this->close.second.x, this->close.second.y);
//
    //for (unsigned int i = 0; i < tmp.size(); i++)
    //    if (!((tmp[i].x == this->close.first.x && tmp[i].y == this->close.first.y) || (tmp[i].x == this->close.second.x && tmp[i].y == this->close.second.y)))
    //        open_pos.push_back(tmp[i]);
    //for (unsigned long i = 0; i < open_pos.size(); i++)
    //    printf("Available coordinates [%f::%f]-> [%c]\n", open_pos[i].x, open_pos[i].y, this->map[open_pos[i].y][open_pos[i].x]);
    //for (unsigned int i = 0; i < open_pos.size(); i++)
    //    dist.push_back(calculateDist(open_pos[i]));
    //auto min_value = std::min_element(dist.begin(), dist.end());
    //setDirections(open_pos[min_value - dist.begin()]);
    //setPos(open_pos[min_value - dist.begin()]);
    //printf("Next coordinates: [%f::%f]\n", open_pos[min_value - dist.begin()].x, open_pos[min_value - dist.begin()].y);
    this->open.push_back({this->_pos, calculateDistObj(this->_pos), 0, 0});

    while (this->open.size() != 0) {
        tmp = getSmallestF();
        this->open.erase(this->open.begin() + tmp.second);
        this->close.push_back(tmp.first);
        current_pos = this->close.back().position;
        if (compareVector(this->targetPosition, current_pos))
            break;
        getAvailableTiles(current_pos);
    }
    for (unsigned int i = 0; i < this->close.size(); i++)
        printf("Node: [%f::%f]\n", this->close[i].position.x, this->close[i].position.y);
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