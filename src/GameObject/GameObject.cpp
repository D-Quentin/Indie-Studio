/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** GameObject
*/

#include "GameObject.hpp"
#include "Game.hpp"
#include <boost/algorithm/string.hpp>
#include "Player.hpp"

GameObject::GameObject(RAYLIB::Vector2 pos, int id) : _pos(pos), _id(id)
{
}

RAYLIB::Vector2 GameObject::getPos()
{
    return (this->_pos);
}

void GameObject::setPos(RAYLIB::Vector2 pos)
{
    this->_pos = pos;
}

int GameObject::getId()
{
    return (this->_id);
}

void GameObject::setId(int id)
{
    this->_id = id;
}

// TYPE;ID:id;X:x;Y:y\n
void GameObject::gestData(std::map<int, GameObject *> *obj, std::string str, Client *client)
{
    int id = 0;
    int pos = 0;
    std::vector<std::string> strs;

    boost::split(strs, str, boost::is_any_of("\n"));
    for (int i = 0; i != strs.size(); i++) {
        pos = str.find("ID:");
        id = std::atoi(str.substr((pos + 3), str.find(";", pos) - pos).c_str());
        if (id < obj->size())
            obj->at(id)->deserialize(str);
        else {
            if (str.find("PLAYER") != std::string::npos) {
                obj->insert(std::pair<int, GameObject *>(obj->size(), new Player()));
                obj->at(obj->size() - 1)->deserialize(str);
            }
        }
    }
}