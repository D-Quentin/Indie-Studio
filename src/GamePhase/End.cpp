/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** End
*/

#include "End.hpp"

End::End()
{
}

End::~End()
{
}

GamePhase End::launch()
{
    this->_tbackground = RAYLIB::LoadTexture("assets/texture/background.png");
    return (this->restart());
}

GamePhase End::restart()
{
    return (endPhase(EndPhase));
}

GamePhase End::endPhase(GamePhase gamePhase)
{
    RAYLIB::DrawTextureEx(this->_tbackground, {0, 0}, 0, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::WHITE);
}
