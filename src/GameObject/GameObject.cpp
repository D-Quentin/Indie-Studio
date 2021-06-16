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
#include "Lobby.hpp"

GameObject::GameObject(RAYLIB::Vector2 pos, int id) : _pos(pos), _id(id)
{
    this->_change = false;
}

RAYLIB::Vector2 GameObject::getPos()
{
    return (this->_pos);
}

void GameObject::setPos(RAYLIB::Vector2 pos)
{
    this->_pos = pos;
}

void GameObject::setPos(RAYLIB::Vector3 pos)
{
    this->_pos = {pos.x, pos.z};
    this->_ypos = pos.y;
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
void GameObject::gestData(std::map<int, GameObject *> &obj, std::string str, Client *&client, Lobby &lobby)
{
    size_t id = 0;
    size_t pos = 0;
    std::vector<std::string> strs;

    boost::split(strs, str, boost::is_any_of("\n"));
    for (size_t i = 0; i != strs.size(); i++) {
        if (strs[i].find(INCOMMING_CONNECTION) != std::string::npos && obj.size() != 0) {
            client->send(obj[lobby.getMe()]->serialize());
            lobby.setPlayer(lobby.getPlayer() + 1);
        }
        if (strs[i].find("READY;") != std::string::npos)
            lobby.setReadyPlayer(lobby.getReadyPlayer() + 1);
        pos = strs[i].find("ID:");
        if (pos == std::string::npos)
            continue;
        id = std::atoi(strs[i].substr((pos + 3), strs[i].find(";", pos) - pos).c_str());
        if (id < obj.size())
            obj.at(id)->deserialize(strs[i]);
        else {
            if (strs[i].find("PLAYER;") != std::string::npos) {
                obj.insert(std::pair<int, GameObject *>(obj.size(), new Player({0, 0}, -1, false)));
                obj.at(obj.size() - 1)->deserialize(strs[i]);
            }
        }
    }
}