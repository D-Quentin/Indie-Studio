/*
** EPITECH PROJECT, 2021
** boost_asio_tests
** File description:
** client_helloworld
*/

#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

using namespace boost;
using namespace boost::asio;

class Client {
    public:
        Client(asio::io_service &io_service, char *host, char *port);
        ~Client();

        void send(std::string message) const;
        std::string read(void) const;

    protected:

    private:
        char *_port;
        char *_host;
        ip::udp::socket _socket;
        ip::udp::endpoint _receiver_endpoint
};

Client::Client(asio::io_service &io_service, char *host, char *port)
{
    this->_host = host;
    this->_port = port;
    ip::udp::resolver resolver(io_service);
    ip::udp::resolver::query query(ip::udp::v4(), this->_host, this->_port);
    this->_receiver_endpoint = *resolver.resolve(query);
    this->_socket(io_service);
    this->_socket.open(ip::udp::v4());
}

void Client::send(std::string message) const
{
    auto message = std::make_shared<std::string>(message);
    this->_socket.send_to(buffer(*message), this->_receiver_endpoint);
}

std::string Client::read(void) const
{
    auto recv_buff = std::make_shared<std::string>("Hello World\n");
    ip::udp::endpoint sender_endpoint;
    size_t len = this->_socket.receive_from(buffer(*recv_buff), sender_endpoint);
    std::cout.write((*recv_buff).data(), len);
}

int main(int ac, char **av)
{
    asio::io_service io_service;
    Client client(io_service, av[1], av[2])

    auto recv_buff = std::make_shared<std::string>("Hello World\n");
    ip::udp::endpoint sender_endpoint;
    size_t len = socket.receive_from(buffer(*recv_buff), sender_endpoint);
    std::cout.write((*recv_buff).data(), len);
    return (0);
}

Client::~Client()
{
    close(this->_socket);
}