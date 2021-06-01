/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** IGamePhase
*/

#ifndef IGAMEPHASE_HPP_
#define IGAMEPHASE_HPP_

enum GamePhase {
    QuitPhase,
    MenuPhase,
    SettingsPhase,
    LobbyPhase
};

class IGamePhase {
    public:
        virtual ~IGamePhase() = default;
        virtual GamePhase launch() = 0;
        virtual GamePhase restart() = 0;

    protected:
    private:
};

#endif /* !IGAMEPHASE_HPP_ */
