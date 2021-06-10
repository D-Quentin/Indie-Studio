/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** main
*/

// #include <iostream>

#include "encapsulation.hpp"
#include "Game.hpp"
#include "Server.hpp"

static const int WIN_HEIGHT = RAYLIB::GetScreenHeight();
static const int WIN_WIDTH = RAYLIB::GetScreenWidth();

void launchServer(int port)
{
    std::cout << "Launching server..." << std::endl;
    boost::asio::io_service io_service;
    udp::resolver resolver(io_service);
    Server server(io_service, port);

    std::cout << "Server is up and running at port " << std::to_string(port) << std::endl;
    std::cout << "You can close this whenever you don't need the server anymore." << std::endl;
    io_service.run();
    std::cout << "Ending server..." << std::endl;
}

int main(int ac, char **av)
{
    int WIN_HEIGHT = RAYLIB::GetScreenHeight();
    int WIN_WIDTH = RAYLIB::GetScreenWidth();

    if (ac == 3 && std::string(av[1]) == "--server") {
        launchServer(std::atoi(av[2]));
        return (0);
    }
    rl::Window win(WIN_WIDTH, WIN_HEIGHT, "Indie Studio");
    Game game;

    //win.fullscreen();
    game.launch(win);
    win.destroy();
    return 0;
}