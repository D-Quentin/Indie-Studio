/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** GamePlay
*/

#include "GamePlay.hpp"

// #define ACTIVE_CAMERA ((this->_isFpCam) ? this->_FPCamera : this->_TopCamera)
#define ACTIVE_CAMERA (this->_TopCamera)

void GamePlay::nonToPoi(std::list<MapBlock> obj)
{
    for (auto it : obj)
        _blocks.push_back(new MapBlock(it));
}

GamePlay::GamePlay()
{
    // _FPCamera =  rl::Camera((RAYLIB::Vector3) { 0, 0, 0 },(RAYLIB::CameraMode) RAYLIB::CAMERA_FIRST_PERSON);
    _player = Player();
    auto pos = _player.getPos();
    _TopCamera = rl::Camera({pos.x, 6, pos.y});
    RAYLIB::ShowCursor();
}

GamePhase GamePlay::launch()
{
    //SET ALL
    std::string path("/home/THE/texture/");
    float size = 1;
    auto mesh = RAYLIB::GenMeshCube(size, size, size);
    auto charMap = main_create_map(2, 1);
    auto texture = RAYLIB::LoadTexture(std::string(path + "texture_minecraft_stone.png").c_str());
    auto model = rl::Models(mesh, texture);
    auto m = Map3D(charMap, model, size);
    _spawn = m._spawns.front();

    _TopCamera.setPosition({_spawn.first, _TopCamera.getPosition().y, _spawn.second});
    _FPCamera.setPosition({_spawn.first, _FPCamera.getPosition().y, _spawn.second});
    this->_mapSize = {charMap.size(), charMap.front().size()};
    this->nonToPoi(m._mapBlocks);
    return GamePlayPhase;
}

GamePhase GamePlay::restart()
{
    RAYLIB::HideCursor();
    while (!RAYLIB::WindowShouldClose()) {
    //updtae attrib from server
        this->handleCamera();
        RAYLIB::BeginDrawing();
        // ACTIVE_CAMERA.begin3D();
        RAYLIB::BeginMode3D(ACTIVE_CAMERA.getCamera());
        this->drawAll();
        // ACTIVE_CAMERA.end3D();
        RAYLIB::EndMode3D();
        RAYLIB::DrawFPS(10, 10);
        RAYLIB::EndDrawing();
        RAYLIB::ClearBackground({255, 255, 255});
    }
    RAYLIB::ShowCursor();
    return MenuPhase;
}

void GamePlay::handleCamera()
{
    //change pov
    if (RAYLIB::IsKeyPressed(RAYLIB::KEY_F5))
        this->_isFpCam = !this->_isFpCam;
    auto oldPos = ACTIVE_CAMERA.getPosition();

    //update camera
        auto ppos = this->_player.getPos();
        ACTIVE_CAMERA.updateCamera({ppos.x, ppos.y});

    //colition player wall
    // auto campos = ACTIVE_CAMERA.getPosition();
    // for (auto it : _blocks) {
    //     auto pos = it->getPos();
    //     if (RAYLIB::CheckCollisionCircleRec({campos.x, campos.z}, 0.5, RAYLIB::Rectangle ({pos.x, pos.y, 0.5, 0.5}))) {
    //         ACTIVE_CAMERA.setPosition(oldPos);
    //         break;
    //     }
    // }
}

void GamePlay::drawAll()
{
    auto oldpos = this->_player.getPos();
    this->_player.update();
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
//     for (auto it : this->_items)
//         it->draw();
    // RAYLIB::DrawPlane((RAYLIB::Vector3){ _mapSize.first / 2, -0.5, _mapSize.second / 2 }, (RAYLIB::Vector2){ _mapSize.first + _mapSize.second, _mapSize.second + _mapSize.first}, RAYLIB::RED); //draw flor
    RAYLIB::DrawGrid(100, 5);
}
