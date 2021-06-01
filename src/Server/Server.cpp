/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Server
*/

#include "Server.hpp"

Server::Server(boost::asio::io_service& io_service, int port) : _socket(io_service, udp::endpoint(udp::v4(), port))
{
    startReceive();
}

void Server::startReceive(void)
{
    this->_socket.async_receive_from(
        boost::asio::buffer(_recv_buffer),
        this->_remote_endpoint,
        boost::bind(
            &Server::handleReceive,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
}

void Server::handleReceive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error || error == boost::asio::error::message_size) {
        boost::shared_ptr<std::string> message(new std::string("New user !"));
        this->_socket.async_send_to(
            boost::asio::buffer(*message),
            this->_remote_endpoint,
            boost::bind(
                &Server::handleSend,
                this,
                message,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred
            )
        );
    }
    this->startReceive();
}

void Server::handleSend(boost::shared_ptr<std::string> message, const boost::system::error_code& error, std::size_t bytes)
{

}

// int main(int ac, char **av)
// {
//     try {
//         boost::asio::io_service io_service;
//         Server server(io_service, atoi(av[1]));
//         io_service.run();
//     }
//     catch (std::exception& e) { 
//         std::cerr << e.what() << std::endl;
//     }
//     return 0;
// }