#include "Ai.hpp"
#include <string>

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