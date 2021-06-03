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

bool Server::isConnectionNew(udp::endpoint endpoint)
{
    for (auto it : this->_connection_pool)
        if (it.second == endpoint)
            return false;
    return true;
}

void Server::startReceive(void)
{
    this->_socket.async_receive_from(
        boost::asio::buffer(_recv_buffer),
        this->_new_endpoint,
        boost::bind(
            &Server::handleReceive,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
}

std::string Server::getUUIDFromString(std::string line)
{
    std::string uuid;
    size_t pos = line.find("UUID:");

    if (pos == std::string::npos)
        return ("");
    pos += 5;
    for (size_t i = pos, j = 0; line[i] != '\0' && line[i] != ';'; i += 1, j += 1)
        uuid[j] = line[i];
    return uuid;
}

void Server::sendToAll(std::string message)
{
    for (auto it : this->_connection_pool)
        this->_socket.send_to(boost::asio::buffer(message), it.second);
}

void Server::sendToSender(std::string message)
{
    this->_socket.send_to(boost::asio::buffer(message), this->_new_endpoint);
}

void Server::sendTo(SEND send, std::string message)
{
    if (send == ALL) {
        this->sendToAll(message);
        // std::thread{Server::sendToAll, std::ref(message)}.detach();
    }
    else if (send == SENDER) {
        this->sendToSender(message);
        // std::thread{Server::sendToSender, std::ref(message)}.detach();
    }
    return;
}


void Server::handleReceive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error || error == boost::asio::error::message_size) {
        std::string line(this->_recv_buffer.begin(), this->_recv_buffer.end());
        if (this->_connection_pool.find(getUUIDFromString(line)) == this->_connection_pool.end()) // If client uuid doesn't exist in connectio pool yet, add it.
            this->_connection_pool[getUUIDFromString(line)] = this->_new_endpoint;
        if (line.find("CONNECTED") != std::string::npos) {
            sendTo(ALL, "New user connected.");
        }
    }
    this->startReceive();
}

bool Server::launchServer(boost::asio::io_service& io_service)
{
    switch (fork()) {
        case (-1):
            return (false);
        case (0):
            return (true);
        default:
            io_service.run();
            return (true);
    }
}

// int main(int ac, char **av)
// {
//     boost::asio::io_service io_service;
//     Server server(io_service, atoi(av[1]));

//     server.launchServer(io_service);
//     while (true) { // TEST -- Occupe le prog pendant que le serv tourne
//         std::cout << "je tourne dans le vide" << std::endl;
//     }
// }