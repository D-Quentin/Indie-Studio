/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Play
*/

#include "Play.hpp"
#include <boost/algorithm/string.hpp>
#include "Ai.hpp"
#include "PowerUp.hpp"

Play::Play()
{
    this->_TopCamera = rl::Camera({0, 6, 0});
    this->_FPCamera =  rl::Camera({ 0, 10, 0 }, RAYLIB::CAMERA_FIRST_PERSON);
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
    this->_tHp = rl::Text("Hp ", 1, 95, 20, RAYLIB::RED);
    this->_shield = RAYLIB::LoadTexture("assets/texture/shield.png");
    this->_heart = RAYLIB::LoadTexture("assets/texture/heart.png");
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
    static RAYLIB::Vector2 clear = {-1000, -1000};
    std::vector<std::map<int, GameObject *>::iterator> to_delet;
    int dead = 0;
    for (auto it = this->_obj.begin(); it != this->_obj.end() ; it++) {
        if (it->second->getObjType() == "Bullet") {
            ((Player *)this->_obj[this->_me])->getBullet().push_back(*((Bullet *)it->second));
            to_delet.push_back(it);
        }
        if (it->second->getObjType() == "Player") {
            if (((Player *)it->second)->isAlive() == false)
                dead += 1;
        }
    }
    if (dead >= this->_player - 1) {
        std::cout << this->_player << std::endl;
        std::cout << dead << std::endl;
        gamePhase = EndPhase;
    }
    for (size_t i = 0; i < to_delet.size(); i++) {
        this->_obj.erase(to_delet[i]);
    }
    
    ((Player *)this->_obj[this->_me])->gest(client, this->_blocks);
    this->reloadPower();
    this->updatePowerUp();
    auto it_items = _items.begin();
    for (auto &it : _items) {
        bool col = RAYLIB::CheckCollisionCircles(it->getPos(), 0.15f, ((Player *)this->_obj[this->_me])->getPos(), 0.15f);
        if (!col) {
            it_items++;
            continue;
        }
        if (it->isWeapon) {
            std::cout << it->getObjType() << std::endl;
            ((Player *)this->_obj[this->_me])->createWeapon(it->getObjType(), 2);
            it->isWear = true;
        }
        else  {
            _power_up.push_back((PowerUp *)it);
            it->isWear = true;
        }
        _items.erase(it_items);
        break;
    }
    if (RAYLIB::IsKeyDown(RAYLIB::KEY_F7)) {
        ((Player *)this->_obj[this->_me])->takeDamage(100);
        ((Player *)this->_obj[this->_me])->takeDamage(100);
    }
    this->_tHp.setText("Hp " + std::to_string(((Player *)this->_obj[this->_me])->getHealth()));
    

    // 3D Drawing
    RAYLIB::BeginMode3D(ACTIVE_CAMERA(((Player *)this->_obj[this->_me])->isAlive()).getCamera());

    // Draw GameObject
    for (auto it = this->_obj.begin(); it != this->_obj.end() ; it++) {
        if (it->second->getId() == (((Player *)this->_obj[this->_me])->getId() + 1) * 1000 || it->second->getId() == (((Player *)this->_obj[this->_me])->getId() + 1) * 1000 + 1)
            continue;
        it->second->draw();
        if (it->second->getObjType() == "Pistol" || it->second->getObjType() == "Rifle" || it->second->getObjType() == "Snip")
            it->second->setPos(clear);
    }

    // Draw Blocks
    RAYLIB::Vector3 campos = ACTIVE_CAMERA(((Player *)this->_obj[this->_me])->isAlive()).getPosition();
    for (auto it2 : this->_blocks) {
        auto pos = it2->getPos();
        if ((pos.y < campos.z + _renderDistance && pos.y > campos.z - _renderDistance) && (pos.x < campos.x + _renderDistance && pos.x > campos.x - _renderDistance))
            it2->draw();
    }

    // Draw flor
    RAYLIB::DrawPlane({ _mapSize.first / 2, -0.01, _mapSize.second / 2 }, { (_mapSize.first + _mapSize.second) * 10, (_mapSize.second + _mapSize.first) * 10}, GROUNDCOLOR);

    for (auto it : this->_items)
        it->draw();
    for (auto it : this->_spawns)
        RAYLIB::DrawPlane({ it.first, 0, it.second}, { 1, 1}, SPAWNCOLOR);
    for (auto it : this->_items)
        RAYLIB::DrawPlane({ it->getPos().x, 0, it->getPos().y}, { 1, 1}, ITEMCOLOR);

    // Set Camera
    RAYLIB::Vector2 pos = ((Player *)this->_obj[this->_me])->getPos();
    if (((Player *)this->_obj[this->_me])->isAlive())
        ACTIVE_CAMERA(((Player *)this->_obj[this->_me])->isAlive()).updateCamera({pos.x, pos.y});
    else
        ACTIVE_CAMERA(((Player *)this->_obj[this->_me])->isAlive()).updateCamera();

    RAYLIB::EndMode3D();

    // 2D Drawing
    this->lifeAndShield();

    ((Player *)this->_obj[this->_me])->getBullet().clear();
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
    RAYLIB::Texture2D texture = RAYLIB::LoadTexture("assets/texture/wall.png");
    rl::Models model(mesh, texture);
    Map3D map3D(this->_map, model, size);

    this->_spawns = map3D._spawns;
    this->placeItems(map3D._items);
    this->_mapSize = {this->_map.size(), this->_map.front().size()};
    for (auto it3 : map3D._mapBlocks)
        _blocks.push_back(new MapBlock(it3));

    for (int i = 0; i != this->_nbAi; i++)
        this->_ai.push_back(new Ai(this->_map));
    ((Player *)this->_obj[this->_me])->createWeapon("Pistol" , 1);
    ((Player *)this->_obj[this->_me])->createWeapon("Pistol" , 2);
    ((Player *)this->_obj[this->_me])->setWeaponUse(1);
    this->_phase = Play::MainPhase;
    return (gamePhase);
}

void Play::placeItems(std::list<std::pair<float, float>> itemsPos)
{
    int rand = 0;

    for (auto it : itemsPos) {
        rand = RAYLIB::GetRandomValue(0, enumToItem.size());
        try {
            auto obj = enumToItem.at((EnumItems)rand);
            obj->setPos(RAYLIB::Vector2{it.first, it.second});
            this->_items.push_back(obj);
        } catch(...) {};
    }
}

void Play::lifeAndShield()
{
    RAYLIB::DrawTextureEx(this->_heart, {785, 975}, 0, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::WHITE);
    RAYLIB::DrawTextureEx(this->_shield, {1055, 975}, 0, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::WHITE);
    RAYLIB::DrawRectangleLines(850, 975, 200, 60, RAYLIB::BLACK);
    RAYLIB::DrawRectangle(851, 976, 198, 58, RAYLIB::GRAY);
    RAYLIB::DrawRectangle(851, 976, (((Player *)this->_obj[this->_me])->getHealth() * 2) - 2, 58, RAYLIB::RED);
    RAYLIB::DrawRectangleLines(1120, 975, 50, 60, RAYLIB::BLACK);
    RAYLIB::DrawRectangle(1121, 976, 48, 58, RAYLIB::GRAY);
    if (((Player *)this->_obj[this->_me])->getShield() == 1)
        RAYLIB::DrawRectangle(1121, 976, 48, 58, RAYLIB::BLUE);
}

void Play::reloadPower()
{
    static auto timeDash = TIMENOW;
    static bool boolDash = true;


    for (const auto &it : _power_up)
        if (it->getPower() == PUDash)
            boolDash = true;
    boolDash = false;
    boolDash = boolDash ? true : false;
    if (!boolDash && CHRONO(timeDash) >= 4000) {
        boolDash = false;
        timeDash = TIMENOW;
        _power_up.push_back(new Dash);
    } else if (boolDash)
        timeDash = TIMENOW;
}

bool Play::compare(PowerUp *f, PowerUp *s)
{
    return f->getPower() == s->getPower();
}

void Play::updatePowerUp()
{
    _power_up.unique(Play::compare);
    for (auto &it : _power_up)
        switch (it->getPower()) {
            case PUSpeed:
                ((Player *)this->_obj[this->_me])->setSpeed(it->update());
                break;
            case PUShield:
                ((Player *)this->_obj[this->_me])->setShield();
                it->use();
                break;
            case PUDash:
                if (RAYLIB::IsKeyPressed(RAYLIB::KEY_ENTER)) {
                    ((Player *)this->_obj[this->_me])->dash();
                    it->use();
                }
                break;
            case PUHealth:
                ((Player *)this->_obj[this->_me])->heal();
                it->use();
                break;
            case PUNothing:
                break;
        }
}