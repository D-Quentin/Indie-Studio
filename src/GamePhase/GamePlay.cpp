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
    std::cerr << "first";
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
    _player.setPos(RAYLIB::Vector2{_spawn.first, _spawn.second});

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
        this->updatePowerUp();
        this->updateLocal();
        this->testThings();
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

void GamePlay::updatePowerUp()
{
    _power_up.push_back(new Dash());
    for (auto &it : _power_up)
        switch (it->getPower()) {
            case PUSpeed:
                it->update();
                break;
            case PUShield:
                _player.setShield();
                it->use();
                break;
            case PUView:
                it->update();
                break;
            case PUDash:
                if (RAYLIB::IsKeyPressed(RAYLIB::KEY_ENTER))
                    _player.dash();
                break;
            case PUNothing:
                break;
        }
}

void GamePlay::testThings()
{
    if (RAYLIB::IsKeyPressed(RAYLIB::KEY_KP_0))
        _weapon = new Pistol();
    else if (RAYLIB::IsKeyPressed(RAYLIB::KEY_KP_1))
        _weapon = new Rifle();
    else if (RAYLIB::IsKeyPressed(RAYLIB::KEY_KP_2))
        _weapon = new Snip();
}

void GamePlay::updateLocal()
{
    //update player
    bool col = false;
    auto oldPlayerPos = _player.getPos();
    bool bullet_player = true;

    this->_player.move();
    // handle player / block colision
    for (auto it : _blocks) {
        auto playerPos = _player.getPos();
        float player_radius = 0.3f;
        auto blockPos = it->getPos();
        RAYLIB::Rectangle blockPhysic = {blockPos.x, blockPos.y, 1, 1};
        bool col = RAYLIB::CheckCollisionCircleRec(playerPos, player_radius, blockPhysic);

        if (col)
            _player.setPos(oldPlayerPos);
        //check collision bullet  /walls
        for (auto &it : _bullet)
            if (RAYLIB::CheckCollisionCircleRec(it.getPos(), 0.05, blockPhysic))
                it.isReal = false;
            else if (bullet_player) {
                if (RAYLIB::CheckCollisionCircles(it.getPos(), 0.05, playerPos, player_radius)) {
                    it.isReal = false;
                    std::cerr << "touch";
                }
            }
        bullet_player = false;
    }
    //end collision
    this->_player.rotate();
    ///update weapon
    _weapon->update(_player.getPos(), _player._rota);
    if (RAYLIB::IsKeyDown(RAYLIB::KEY_SPACE))
        _bullet.push_back(_weapon->shoot());
    for (auto &it : _bullet) {
        it.update(); /// update pos
        it.draw(); // draw
        if (!it.isReal) {// check if element is good
            _bullet.remove(it); //mevoe if isnt good
            break;
        }
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
