/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** GamePlay
*/

#ifndef GAMEPLAY_HPP_
#define GAMEPLAY_HPP_

#include <list>
#include <vector>

#include "GamePhase.hpp"
#include "BlockObject.hpp"
#include "EntityObjects.hpp"
#include "Item.hpp"
#include "Map.hpp"
#include "Map3D.hpp"
#include "Player.hpp"
#include "Encapsulation/Camera.hpp"
#include "Encapsulation/Gamepad.hpp"
#include "Encapsulation/Window.hpp"
#include "Encapsulation/Text.hpp"
#include "Weapon.hpp"
#include "PowerUp.hpp"

#define GROUNDCOLOR {119,136,153, 255}
#define SPAWNCOLOR {233,150,122, 255}
#define ITEMCOLOR {42, 157, 244, 255}

class GamePlay{
    public:
        GamePlay();
        ~GamePlay() = default;

        GamePhase launch();
        GamePhase restart();

    private: //methodes
        //set
        void setBlocks(std::list<BlockObject*> obj) {_blocks = obj;};
        void setEnemies(std::list<EntityObjects*> obj) {_enemies = obj;};
        void setItems(std::list<game_object::Item*> obj) {_items = obj;};
        void nonToPoi(std::list<MapBlock>);

        //alive methode
        void updateLocal();
        void updatePowerUp();
        void testThings();
        void delFalseBullet();
        void reloadPower();

        //spec method
        //todo

        //other methods
        void aliveCall();
        void specCall();
        void drawAll();

    private: //attr
        Player _player;
        RAYLIB::Vector2 _oldPlayerPos;
        std::list<BlockObject*> _blocks;
        std::list<EntityObjects*> _enemies;
        std::list<game_object::Item*> _items;
        std::list<Bullet> _bullet;
        int _renderDistance = 40;
        Weapon *_weapon;
        std::list<PowerUp*> _power_up;
        //server
        rl::Camera _FPCamera;
        rl::Camera _TopCamera;
        Gamepad _gmp = Gamepad(0);
        bool _isFpCam = true;
        std::pair<float, float> _mapSize;
        std::pair<float, float> _spawn;
        std::list<std::pair<float, float>> _spawns;
};

#endif /* !GAMEPLAY_HPP_ */
