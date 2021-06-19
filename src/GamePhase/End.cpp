/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** End
*/

#include "End.hpp"
#include "PowerUp.hpp"

End::End()
{
}

End::~End()
{
}

GamePhase End::launch(std::string winner)
{
    this->_tbackground = RAYLIB::LoadTexture("assets/texture/endBack.png");
    this->_tRocket = RAYLIB::LoadTexture("assets/texture/victory.png");
    this->_tReturn = rl::Text("Return", 9, 88, 29, RAYLIB::BLACK);
    this->_bReturn = Button("assets/texture/button.png", 3, 85, 21.4, 10);
    return (this->restart(winner));
}

GamePhase End::restart(std::string winner)
{
    return (endPhase(EndPhase, winner));
}

GamePhase End::endPhase(GamePhase gamePhase, std::string winner)
{
    static auto time = TIMENOW;
    static auto e = TIMENOW;
    static int i = 0;
    float aze = 0;

    winner = "Quentin";
    if (this->_bReturn.isClicked())
        gamePhase = MenuPhase;
    if (CHRONO(time) >= 1000)
        i++;
    if (i != 0)
        if (CHRONO(e) >= 200) {
            e = TIMENOW;
            i++;
        }
    aze = (i/11);
    RAYLIB::DrawTextureEx(this->_tbackground, {0, 0}, 0, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::WHITE);
    RAYLIB::DrawTextureEx(this->_tRocket, {600, (float)800-i}, -45, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::WHITE);
    this->_tName = rl::Text(winner, 45, (float)71-aze, 29, RAYLIB::BLACK);
    this->_bReturn.draw();
    this->_tReturn.draw();
    this->_tName.draw();
    return (gamePhase); 
}
