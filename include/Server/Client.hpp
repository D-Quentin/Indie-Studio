/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>

static const int STR_MAX_LEN = 1024;

using namespace boost::asio::ip;

class Client {
    public:
        Client(boost::asio::io_service &io_service, std::string host, int port);
        ~Client() = default;

        // Méthodes
        void send(std::string str);

    private:
        // Méthodes
        void startReceive(void);
        void handleReceive(const boost::system::error_code& error, std::size_t bytes_transferred);

        // Attributs
        udp::socket _socket;
        udp::endpoint _remote_endpoint;
        boost::array<char, STR_MAX_LEN> _recv_buffer;
};

#endif /* !CLIENT_HPP_ */
