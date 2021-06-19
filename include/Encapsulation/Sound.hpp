/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** sound
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

#include "include.hpp"

class Sound
{
    public:
        Sound();
        ~Sound();
        void init();
        void playSniperShoot();
        void playGunShoot();
        void playRiffleShoot();
        void playWallBreak();
        void playTakeDamage();
        void playMenuMusic();
        void playGameMusic();
        void playEndMusic();
    private:
        RAYLIB::Music _sniperShoot;
        RAYLIB::Music _gunShoot;
        RAYLIB::Music _riffleShoot;
        RAYLIB::Music _wallBreak;
        RAYLIB::Music _takeDamage;
        RAYLIB::Music _menuMusic;
        RAYLIB::Music _gameMusic;
        RAYLIB::Music _endMusic;
};

#endif /* !SOUND_HPP_ */
