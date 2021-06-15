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
    // RAYLIB::ShowCursor();
    this->_weapon = new Pistol(pos);
    Pistol(pos).update({0, 0}, 0);
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
    // RAYLIB::HideCursor();
    while (!RAYLIB::WindowShouldClose()) {
    //updtae attrib from server
        RAYLIB::BeginDrawing();

        // ACTIVE_CAMERA.begin3D();
        RAYLIB::BeginMode3D(ACTIVE_CAMERA.getCamera());
        this->updateLocal();

        this->drawAll();
        // ACTIVE_CAMERA.end3D();
        RAYLIB::EndMode3D();
        RAYLIB::DrawFPS(10, 10);
        rl::Text(std::to_string(_player._rota), 15, 10, 25, {255, 0, 0, 255}).draw();

        RAYLIB::EndDrawing();
        RAYLIB::ClearBackground({255, 255, 255, 255});
    }
    // RAYLIB::ShowCursor();
    return MenuPhase;
}

void GamePlay::updateLocal()
{
    static std::list<Bullet> bullet;
    //update player
    bool col = false;
    auto oldPlayerPos = _player.getPos();

    this->_player.move();
    // handle player / block colision
    for (auto it : _blocks) {
        auto playerPos = _player.getPos();
        auto blockPos = it->getPos();
        col = RAYLIB::CheckCollisionCircleRec(playerPos, 0.5, {blockPos.x, blockPos.y, 1, 1});

        if (col) {
            _player.setPos(oldPlayerPos);
            break;
        }
    }
    //end collision
    this->_player.rotate();
    ///update weapon
    _weapon->update(_player.getPos(), _player._rota);
    if (RAYLIB::IsKeyPressed(RAYLIB::KEY_SPACE)) {
        auto b = _weapon->shoot();
        if (b.isReal)
            bullet.push_back(b);
    }
    for (auto &it : bullet) {
        it.update();
        it.draw();
    }

    //update camera
        auto ppos = this->_player.getPos();
        ACTIVE_CAMERA.updateCamera({ppos.x, ppos.y});
}

void GamePlay::drawAll()
{
    // auto oldpos = this->_player.getPos();
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
//     for (auto it : this->_items)
//         it->draw();
    // RAYLIB::DrawPlane((RAYLIB::Vector3){ _mapSize.first / 2, -0.5, _mapSize.second / 2 }, (RAYLIB::Vector2){ _mapSize.first + _mapSize.second, _mapSize.second + _mapSize.first}, RAYLIB::RED); //draw flor
    RAYLIB::DrawGrid(100, 5);
    // std::cerr << "beg" << std::endl;
    // auto bx = RAYLIB::MeshBoundingBox(_player._model._model.meshes[0]);
    // std::cerr << "min x:" << bx.min.x << " y:" << bx.min.y << " z:" << bx.min.z << std::endl;
    // std::cerr << "max x:" << bx.max.x << " y:" << bx.max.y << " z:" << bx.max.z << std::endl;
    // std::cerr << "end" << std::endl;
}
