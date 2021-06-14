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
        void updateLocal();

        //other methods
        void drawAll();

    private: //attr
        Player _player;
        std::list<BlockObject*> _blocks;
        std::list<EntityObjects*> _enemies;
        std::list<game_object::Item*> _items;
        int _renderDistance = 40;
        Weapon *_weapon;
        //power-up
        //server
        rl::Camera _FPCamera;
        rl::Camera _TopCamera;
        Gamepad _gmp = Gamepad(0);
        bool _isFpCam = true;
        std::pair<float, float> _mapSize;
        std::pair<float, float> _spawn;
};

#endif /* !GAMEPLAY_HPP_ */
