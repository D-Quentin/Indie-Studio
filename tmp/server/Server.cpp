/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** server
*/

#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

using boost::asio::ip::udp;
using namespace boost::asio;

static const int ERROR_EXIT = 84;

class Server {
    public:
        // Special
        Server(boost::asio::io_service &service, int port);

    protected:

    private:
        // Méthodes
        void startReceive(void);
        void handleReceive(const boost::system::error_code &error, std::size_t bytes_transferred);
        void handleSend(std::shared_ptr<std::string> message, const boost::system::error_code &ec, std::size_t bytes_transferred);

        // Attributs
        int _port;
        udp::socket _socket;
        std::string _recvBuffer;
        udp::endpoint _remoteEndPoint;
};

Server::Server(boost::asio::io_service &service, int port) : _socket(service, udp::endpoint(udp::v4(), port)), _port(port)
{
    this->startReceive();
}

void Server::startReceive(void)
{
    this->_socket.async_receive_from(
        buffer(this->_recvBuffer),
        this->_remoteEndPoint,
        boost::bind(
            &Server::handleReceive,
            this,
            placeholders::error,
            placeholders::bytes_transferred
        )
    );
}

void Server::handleReceive(const boost::system::error_code &error, std::size_t bytes_transferred)
{
    if (!error || error == error::message_size) {
        auto message = std::make_shared<std::string>("Hello World\n");
        this->_socket.async_send_to(
            buffer(*message),
            this->_remoteEndPoint,
            boost::bind(&Server::handleSend, this, message, placeholders::error, placeholders::bytes_transferred)
        );
    }
}

void Server::handleSend(std::shared_ptr<std::string> message, const boost::system::error_code &ec, std::size_t bytes_transferred)
{
    startReceive();
}

int main(int ac, char **av)
{
    int port = -1;
    boost::asio::io_service service;

    if (av[1] == NULL || (port = atoi(av[1])) <= 0)
        return (0);
    Server server(service, port);
    service.run();
    return (1);
}