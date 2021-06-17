/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Play
*/

#include "Play.hpp"
#include <boost/algorithm/string.hpp>
#include "Ai.hpp"

Play::Play()
{
    this->_TopCamera = rl::Camera({0, 6, 0});
    this->_nbAi = 0;
}

Play::~Play()
{
}

GamePhase Play::launch(Client *&client, Lobby &lobby)
{
    this->_host = lobby.isHost();
    this->_player = lobby.getPlayer();
    this->_obj = lobby.getObj();
    this->_me = lobby.getMe();
    this->_phase = Play::JoinPhase;
    return (this->restart(client, lobby));
}

GamePhase Play::restart(Client *&client, Lobby &lobby)
{
    GamePhase gamePhase = PlayPhase;

    switch (this->_phase) {
    case Play::MainPhase:
        gamePhase = this->mainPhase(gamePhase, client);
        break;
    case Play::JoinPhase:
        gamePhase = this->joinPhase(gamePhase, client, lobby);
        break;

    default:
        break;
    }

    return (gamePhase);
}

GamePhase Play::mainPhase(GamePhase gamePhase, Client *&client)
{
    GameObject::gestData(this->_obj, client->read(), client, *this);
    ((Player *)this->_obj[this->_me])->gest(client);

    // 3D Drawing
    RAYLIB::BeginMode3D(this->_TopCamera.getCamera());

    // Set Camera
    RAYLIB::Vector2 pos = ((Player *)this->_obj[this->_me])->getPos();
    _TopCamera.updateCamera({pos.x, pos.y});

    // Draw GameObject
    for (auto it = this->_obj.begin(); it != this->_obj.end() ; it++) {
        it->second->draw();
    }

    // Draw Blocks
    RAYLIB::Vector3 campos = this->_TopCamera.getPosition();
    for (auto it2 : this->_blocks) {
        auto pos = it2->getPos();
        if ((pos.y < campos.z + _renderDistance && pos.y > campos.z - _renderDistance) && (pos.x < campos.x + _renderDistance && pos.x > campos.x - _renderDistance))
            it2->draw();
    }

    RAYLIB::DrawGrid(1000, 10);
    RAYLIB::EndMode3D();

    return (gamePhase);
}

GamePhase Play::joinPhase(GamePhase gamePhase, Client *&client, Lobby &lobby)
{
    rl::Window::loading();
    std::string tmp = "";

    if (this->_host) { // Loading and sending map
        this->_map = main_create_map(this->_player, 1);
        client->send("MAP_START;");
        for (size_t i = 0; i != this->_map.size(); i++) {
            for (size_t j = 0; j != this->_map[i].size(); j++)
                tmp.push_back(this->_map[i][j]);
            client->send(tmp + ";");
            tmp = "";
        }
        #if defined(_WIN32)
            Sleep(3000);
        #else
            sleep(3);
        #endif
        size_t i = 0;
        size_t j = 0;
        auto it = this->_obj.begin();
        while (i != this->_map.size()) {
            while (j != this->_map[i].size()) {
                if (this->_map[i][j] == 'S') {
                    it->second->setPos(RAYLIB::Vector2{(float)j, (float)i});
                    client->send(it->second->serialize());
                    it++;
                }
                j++;
            }
            i++;
            j = 0;
        }
        #if defined(_WIN32)
            Sleep(1000);
        #else
            sleep(1);
        #endif
    } else { // Getting the map
        #if defined(_WIN32)
            Sleep(2000);
        #else
            sleep(2);
        #endif
        std::string map = client->read();
        std::vector<std::string> split_map;
        std::vector<char> tmp_char;
        boost::split(split_map, map, boost::is_any_of(";"));
        size_t i = 0;
        while (split_map[i].find("MAP_START") == std::string::npos)
            i++;
        i++;
        for (; i != split_map.size(); i++) {
            for (size_t j = 0; j != split_map[i].size(); j++)
                tmp_char.push_back(split_map[i][j]);
            this->_map.push_back(tmp_char);
            tmp_char.clear();
        }
        #if defined(_WIN32)
            Sleep(2000);
        #else
            sleep(2);
        #endif
    }
    GameObject::gestData(this->_obj, client->read(), client, *this);

    // Creating 3D map
    float size = 1;
    RAYLIB::Mesh mesh = RAYLIB::GenMeshCube(size, size, size);
    RAYLIB::Texture2D texture = RAYLIB::LoadTexture("");
    rl::Models model(mesh, texture);
    Map3D map3D(this->_map, model, size);
    this->_mapSize = {this->_map.size(), this->_map.front().size()};
    for (auto it3 : map3D._mapBlocks)
        _blocks.push_back(new MapBlock(it3));

    for (int i = 0; i != this->_nbAi; i++)
        this->_ai.push_back(new Ai(this->_map));
    this->_phase = Play::MainPhase;
    return (gamePhase);
}
