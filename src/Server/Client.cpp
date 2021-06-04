/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Client
*/

#include "Client.hpp"
#include "Server.hpp"
#include "Game.hpp"

Client::Client(std::string host, int port)
{
    this->_str_received = "";
    this->_io_service = new boost::asio::io_service;
    this->_socket = new udp::socket(*this->_io_service, udp::v4());
    this->_uuid = boost::lexical_cast<std::string>(this->uuid_generator());
    this->_remote_endpoint = boost::asio::ip::udp::endpoint(address::from_string(host), port);
    this->send(INCOMMING_CONNECTION);
    this->startReceive();
    // std::thread run_thread([&]{this->_io_service->run();});
    this->_io_service->run();
}

void Client::startReceive(void)
{
    this->_socket->async_receive_from(
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
    if (!error || error == boost::asio::error::message_size || bytes_transferred > 0)
        this->_str_received = std::string(reinterpret_cast<const char*>(this->_recv_buffer.data()), bytes_transferred);
    this->startReceive();
}

std::string Client::read(void)
{
    std::string rd = this->_str_received;

    this->_str_received = "";
    return (rd);
}

void Client::send(std::string str)
{
    std::string new_str = "UUID:" + this->_uuid + ";" + str;
    boost::shared_ptr<std::string> message(new std::string(new_str));

    this->_socket->send_to(boost::asio::buffer(*message), this->_remote_endpoint);
}

std::string Client::getReponse(void)
{
    std::string str;
    auto time = timeNow;

    while(Chrono(time) <= 5000) {
        str = this->read();
        if (str.empty() == false)
            return (str);
    }
    return (TIMEOUT_CONNECTION);
}

void Client::launch()
{
    // boost::thread (boost::bind(&boost::asio::io_service::run, &(*this->_io_service)));
    // std::thread run_thread([&]{this->_io_service->run();});
    // std::thread thr(Client, host, port);
    // thr.detach();
    // Client(host, port);

}

// int main(int ac, char **av)
// {
//     int port = -1;

//     if (ac != 3 || (port = atoi(av[2])) <= 0)
//         return 1;

//     boost::asio::io_service io_service;
//     Client client(io_service, av[1], port);
//     client.launch(io_service);
// }