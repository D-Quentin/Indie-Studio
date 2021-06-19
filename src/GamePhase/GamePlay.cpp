/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** GamePlay
*/

#include "GamePlay.hpp"

void GamePlay::nonToPoi(std::list<MapBlock> obj)
{
    for (auto it : obj)
        _blocks.push_back(new MapBlock(it));
}

GamePlay::GamePlay()
{
    _FPCamera =  rl::Camera((RAYLIB::Vector3) { 0, 10, 0 },(RAYLIB::CameraMode) RAYLIB::CAMERA_FIRST_PERSON);
    _player = Player();
    auto pos = _player.getPos();
    _TopCamera = rl::Camera({pos.x, 6, pos.y});
    this->_weapon = new Pistol(pos);
}

void GamePlay::placeItems(std::list<std::pair<float, float>> itemsPos)
{
    int rand = 0;

    for (auto it : itemsPos) {
        rand = RAYLIB::GetRandomValue(0, enumToItem.size());
        try {
            auto obj = enumToItem.at((EnumItems)rand);
            obj->setPos(RAYLIB::Vector2{it.first, it.second});
            _items.push_back(obj);
        } catch(...) {};
    }
}

GamePhase GamePlay::launch()
{
    //SET ALL
    float size = 1;
    auto mesh = RAYLIB::GenMeshCube(size, size, size);
    auto charMap = main_create_map(5, 1);
    auto texture = RAYLIB::LoadTexture(std::string("assets/texture/wall.png").c_str());
    auto model = rl::Models(mesh, texture);
    auto m = Map3D(charMap, model, size);

    placeItems(m._items);
    _spawns = m._spawns;
    _spawn = m._spawns.front();
    _player.setPos(RAYLIB::Vector2{_spawn.first, _spawn.second});
    _TopCamera.setPosition({_spawn.first, _TopCamera.getPosition().y, _spawn.second});
    _FPCamera.setPosition({_spawn.first, _FPCamera.getPosition().y, _spawn.second});
    this->_mapSize = {charMap.size(), charMap.front().size()};
    this->nonToPoi(m._mapBlocks);
    return GamePlayPhase;
}

void GamePlay::lifeAndShield()
{
    static int i = 0;
    if (i == 0) {
        this->_shield = RAYLIB::LoadTexture(std::string("assets/texture/shield.png").c_str());
        this->_heart = RAYLIB::LoadTexture(std::string("assets/texture/heart.png").c_str());
        i++;
    }
    RAYLIB::DrawTextureEx(this->_heart, {785, 975}, 0, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::WHITE);
    RAYLIB::DrawTextureEx(this->_shield, {1055, 975}, 0, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::WHITE);
    RAYLIB::DrawRectangleLines(850, 975, 200, 60, RAYLIB::BLACK);
    RAYLIB::DrawRectangle(851, 976, 198, 58, RAYLIB::GRAY);
    RAYLIB::DrawRectangle(851, 976, (this->_player.getHealth() * 2) - 2, 58, RAYLIB::RED);
    RAYLIB::DrawRectangleLines(1120, 975, 50, 60, RAYLIB::BLACK);
    RAYLIB::DrawRectangle(1121, 976, 48, 58, RAYLIB::GRAY);
    if (this->_player.getShield() == 1)
        RAYLIB::DrawRectangle(1121, 976, 48, 58, RAYLIB::BLUE);
    RAYLIB::EndDrawing();
    RAYLIB::ClearBackground({255, 255, 255, 255});
}

GamePhase GamePlay::restart()
{
    while (!RAYLIB::WindowShouldClose()) {
        _oldPlayerPos = _player.getPos();
    //updtae attrib from server
        RAYLIB::BeginDrawing();
        if (_player.isAlive()) {
            this->aliveCall();
        } else {
            this->specCall();
        }
        this->drawAll();
        RAYLIB::DrawFPS(10, 10);
        lifeAndShield();
    }
    // RAYLIB::ShowCursor();
    return MenuPhase;
}

void GamePlay::aliveCall()
{
    this->reloadPower();
    this->updatePowerUp();
    this->updateLocal();
    this->testThings();
}

void GamePlay::specCall()
{
    //todo
    ACTIVE_CAMERA.updateCamera();
}

void GamePlay::drawAll()
{
    RAYLIB::BeginMode3D(ACTIVE_CAMERA.getCamera());

    _weapon->draw();

    this->_player.draw(); // draw self
    // draw all lists
    auto campos = ACTIVE_CAMERA.getPosition();
    for (auto it : this->_blocks) {
        auto pos = it->getPos();
        if ((pos.y < campos.z + _renderDistance && pos.y > campos.z - _renderDistance) && (pos.x < campos.x + _renderDistance && pos.x > campos.x - _renderDistance))
            it->draw();
    }
//     for (auto it : this->_enemies)
//         it->draw();
    for (auto it : this->_items)
        it->draw();
    for (auto &it : _bullet) {
        it.update();
        it.draw(); // draw
    }
    RAYLIB::DrawPlane((RAYLIB::Vector3){ _mapSize.first / 2, -0.01, _mapSize.second / 2 }, (RAYLIB::Vector2){ _mapSize.first + _mapSize.second, _mapSize.second + _mapSize.first}, GROUNDCOLOR); //draw flor
    for (auto it : _spawns)
        RAYLIB::DrawPlane((RAYLIB::Vector3){ it.first, 0, it.second}, (RAYLIB::Vector2){ 1, 1}, SPAWNCOLOR);
    for (auto it : _items)
        RAYLIB::DrawPlane((RAYLIB::Vector3){ it->getPos().x, 0, it->getPos().y}, (RAYLIB::Vector2){ 1, 1}, ITEMCOLOR);
    RAYLIB::EndMode3D();
}
