/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Client
*/

#include "Client.hpp"

Client::Client(boost::asio::io_service &io_service, std::string host, int port) : _socket(io_service, udp::endpoint(udp::v4(), 0))
{
    this->_remote_endpoint = boost::asio::ip::udp::endpoint(address::from_string(host), port);
    // this->_socket.send_to(boost::asio::buffer("Connect"), this->_remote_endpoint);
    this->startReceive();
}

void Client::startReceive(void)
{
    this->_socket.async_receive_from(
        boost::asio::buffer(_recv_buffer),
        _remote_endpoint,
        boost::bind(
            &Client::handleReceive,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
}

void Client::handleReceive(const boost::system::error_code& error, std::size_t bytes_transferred)
{;
    if (!error || error == boost::asio::error::message_size || bytes_transferred > 0) {
        std::cout << std::string(reinterpret_cast<const char*>(this->_recv_buffer.data()), bytes_transferred) << std::endl;
    }
    this->startReceive();
}

void Client::send(std::string str)
{
    boost::shared_ptr<std::string> message(new std::string(str));
    this->_socket.send_to(boost::asio::buffer(*message), this->_remote_endpoint);
}

// int main(int ac, char* av[])
// {
//     try
//     {
//         int port = -1;
//         if (ac != 3 || (port = atoi(av[2])) <= 0)
//             return 1;
//         boost::asio::io_service io_service;
//         Client client(io_service, av[1], port);
//         io_service.run();
//     }
//     catch (std::exception& e) {
//         std::cerr << e.what() << std::endl;
//     }
//     return 0;
// }