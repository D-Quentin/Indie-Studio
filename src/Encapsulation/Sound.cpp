/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Sound
*/

#include "Sound.hpp"

rl::Sound::Sound()
{
    RAYLIB::InitAudioDevice();
    this->_sniperShoot = RAYLIB::LoadSound("assets/sound/sniper.mp3");
    //this->_endMusic = RAYLIB::LoadSound("assets/sound/");
    this->_dead = RAYLIB::LoadSound("assets/sound/mort.mp3");
    //this->_gameMusic = RAYLIB::LoadSound("assets/sound/");
    this->_gunShoot = RAYLIB::LoadSound("assets/sound/pistolet.mp3");
    this->_menuMusic = RAYLIB::LoadSound("assets/sound/pnl_uranus.mp3");
    this->_riffleShoot = RAYLIB::LoadSound("assets/sound/m4.mp3");
    this->_takeDamage = RAYLIB::LoadSound("assets/sound/damage.mp3");
    this->_wallBreak = RAYLIB::LoadSound("assets/sound/explosion.mp3");
}

rl::Sound::~Sound()
{
}


void rl::Sound::playSniperShoot()
{
    RAYLIB::PlaySound(this->_sniperShoot);
}

void rl::Sound::playEndMusic()
{
    RAYLIB::PlaySound(this->_endMusic);
}

void rl::Sound::playGameMusic()
{
    RAYLIB::PlaySound(this->_gameMusic);
}

void rl::Sound::playGunShoot()
{
    RAYLIB::PlaySound(this->_gunShoot);
}

void rl::Sound::playMenuMusic()
{
    RAYLIB::PlaySound(this->_menuMusic);
}

void rl::Sound::playRiffleShoot()
{
    RAYLIB::PlaySound(this->_riffleShoot);
}

void rl::Sound::playTakeDamage()
{
    RAYLIB::PlaySound(this->_takeDamage);
}

void rl::Sound::playWallBreak()
{
    RAYLIB::PlaySound(this->_wallBreak);
}

void rl::Sound::playDead()
{
    RAYLIB::PlaySound(this->_dead);
}

void rl::Sound::stopAllMusic()
{
    RAYLIB::StopSound(this->_menuMusic);
    RAYLIB::StopSound(this->_gameMusic);
    RAYLIB::StopSound(this->_endMusic);
}