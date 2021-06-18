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
    _items.push_front(new Speed);
    _items.front()->setPos(RAYLIB::Vector2{-5, -5});
    _items.push_front(new Shield);
    _items.front()->setPos(RAYLIB::Vector2{-6, -5});
    _items.push_front(new Speed);
    _items.front()->setPos(RAYLIB::Vector2{-7, -5});
    _items.push_front(new Rifle);
    _items.front()->setPos(RAYLIB::Vector2{-10, -5});
}

GamePhase GamePlay::launch()
{
    //SET ALL
    float size = 1;
    auto mesh = RAYLIB::GenMeshCube(size, size, size);
    auto charMap = main_create_map(2, 1);
    auto texture = RAYLIB::LoadTexture(std::string("assets/texture/wall.png").c_str());
    auto model = rl::Models(mesh, texture);
    auto m = Map3D(charMap, model, size);

    _spawns = m._spawns;
    _spawn = m._spawns.front();
    _player.setPos(RAYLIB::Vector2{_spawn.first, _spawn.second});
    _TopCamera.setPosition({_spawn.first, _TopCamera.getPosition().y, _spawn.second});
    _FPCamera.setPosition({_spawn.first, _FPCamera.getPosition().y, _spawn.second});
    this->_mapSize = {charMap.size(), charMap.front().size()};
    this->nonToPoi(m._mapBlocks);
    return GamePlayPhase;
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

        RAYLIB::EndDrawing();
        RAYLIB::ClearBackground({255, 255, 255, 255});
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
