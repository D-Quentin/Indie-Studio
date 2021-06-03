/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <ctime>
#include <functional>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include "GameObject.hpp"

using namespace boost::asio::ip;
using namespace boost::asio;

class Server
{
    enum SEND {
        ALL,
        SENDER,
    };

    public:
        // Spéciales
        Server(boost::asio::io_service& io_service, int port);
        ~Server() = default;

        // Méthodes
        bool launchServer(boost::asio::io_service& io_service);

    private:
        // Méthodes
        void startReceive(void);
        void sendToAll(std::string message);
        void sendToSender(std::string message);
        bool isConnectionNew(udp::endpoint endpoint);
        std::string getUUIDFromString(std::string line);
        void sendTo(SEND send, std::string message);
        void handleReceive(const boost::system::error_code& error, std::size_t bytes);
        void handleSend(boost::shared_ptr<std::string> message, const boost::system::error_code& error, std::size_t bytes);

        // Attributs
        udp::socket _socket;
        udp::endpoint _new_endpoint;
        std::map<int, GameObject *> _obj;
        boost::array<char, 1> _recv_buffer;
        std::map<std::string, udp::endpoint> _connection_pool;
};

#endif /* !SERVER_HPP_ */