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

using namespace boost::asio::ip;
using namespace boost::asio;

class Server
{
    public:
        Server(boost::asio::io_service& io_service, int port);
        ~Server() = default;

    private:
        // Méthodes
        void startReceive(void);
        void handleReceive(const boost::system::error_code& error, std::size_t bytes);
        void handleSend(boost::shared_ptr<std::string> message, const boost::system::error_code& error, std::size_t bytes);

        // Attributs
        udp::socket _socket;
        udp::endpoint _remote_endpoint;
        boost::array<char, 1> _recv_buffer;
};

#endif /* !SERVER_HPP_ */