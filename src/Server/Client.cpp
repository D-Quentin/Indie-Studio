/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Client
*/

#include "Client.hpp"
#include "Message.hpp"
#include "Game.hpp"

Client::Client(boost::asio::io_service &io_service, std::string host, int port) : _socket(io_service, udp::endpoint(udp::v4(), 0))
{
    this->_remote_endpoint = boost::asio::ip::udp::endpoint(address::from_string(host), port);
    this->send(INCOMMING_CONNECTION);
    this->startReceive();
}

std::string Client::read(void)
{
    std::string str = this->_recv;

    this->_recv = "";
    return (str);
}

void Client::send(std::string str)
{
    std::cout << "Send to server: " << str << std::endl;
    this->_socket.send_to(boost::asio::buffer(str), this->_remote_endpoint);
}

void Client::startReceive(void)
{
    this->_socket.async_receive_from(
        boost::asio::buffer(this->_recv),
        this->_remote_endpoint,
        boost::bind(
            &Client::handleReceive,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
}

void Client::handleReceive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error || error == boost::asio::error::message_size) {
        this->_all_recv += this->_recv;
    }
    this->startReceive();
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

void Client::launch(boost::asio::io_service &io_service)
{
    boost::thread run_thread(boost::bind(&boost::asio::io_service::run, boost::ref(io_service)));
}


























































































































// #include "Client.hpp"
// #include "Server.hpp"
// #include "Game.hpp"

// Client::Client(boost::asio::io_context &io_context, std::string host, int port) : _socket(io_context, udp::endpoint(udp::v4(), 0))
// {
//     this->_str_received = "";
//     this->_uuid = boost::lexical_cast<std::string>(this->uuid_generator());
//     this->_remote_endpoint = boost::asio::ip::udp::endpoint(address::from_string(host), port);
//     this->send(INCOMMING_CONNECTION);
//     this->startReceive();
//     // io_service.poll();
// }

// void Client::startReceive(void)
// {
//     this->_socket.async_receive_from(
//         boost::asio::buffer(_recv_buffer),
//         _remote_endpoint,
//         boost::bind(
//             &Client::handleReceive,
//             this,
//             boost::asio::placeholders::error,
//             boost::asio::placeholders::bytes_transferred
//         )
//     );
// }

// void Client::handleReceive(const boost::system::error_code& error, std::size_t bytes_transferred)
// {
//     if (!error || error == boost::asio::error::message_size || bytes_transferred > 0) {
//         this->_str_received = std::string(reinterpret_cast<const char*>(this->_recv_buffer.data()), bytes_transferred);
//         std::cout << this->_str_received << std::endl;
//     }
//     this->startReceive();
// }

// std::string Client::read(void)
// {
//     std::string rd = this->_str_received;
//     size_t reply_length = this->_socket.receive_from(boost::asio::buffer(this->_str_received, STR_MAX_LEN), this->_sender_endpoint);
// }

// void Client::send(std::string str)
// {
//     std::string new_str = "UUID:" + this->_uuid + ";" + str;
//     boost::shared_ptr<std::string> message(new std::string(new_str));

//     this->_socket.send_to(boost::asio::buffer(*message), this->_remote_endpoint);
// }

// std::string Client::getReponse(void)
// {
//     std::string str;
//     auto time = timeNow;

//     while(Chrono(time) <= 5000) {
//         str = this->read();
//         if (str.empty() == false)
//             return (str);
//     }
//     return (TIMEOUT_CONNECTION);
// }

// void Client::launch(boost::asio::io_service &io_service)
// {
//     std::shared_ptr<boost::asio::io_service::work> work(new boost::asio::io_service::work(io_service));
//     boost::thread run_thread(boost::bind(&boost::asio::io_service::run, boost::ref(io_service)));
//     // boost::thread t(&boost::asio::io_service::run, &io_service);
// }

// // int main(int ac, char **av)
// // {
// //     int port = -1;

// //     if (ac != 3 || (port = atoi(av[2])) <= 0)
// //         return 1;

// //     boost::asio::io_service io_service;
// //     Client client(io_service, av[1], port);
// //     client.launch(io_service);
// // }