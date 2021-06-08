/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Client
*/

#include "Client.hpp"
#include "Message.hpp"
#include "Game.hpp"

Client::Client(std::string host, int port) : _socket(this->_io_service, udp::endpoint(udp::v4(), 0))
{
    udp::resolver resolver(this->_io_service);
    udp::resolver::query query(udp::v4(), host, std::to_string(port));
    this->_remote_endpoint = *(resolver.resolve(query));
    this->startReceive();
}

std::string Client::read(void)
{
    std::string str(this->_all_recv);

    this->_all_recv = "";
    return (str);
}

void Client::send(std::string str)
{
    this->_socket.send_to(boost::asio::buffer(str), this->_remote_endpoint);
}

void Client::startReceive(void)
{
    this->_socket.async_receive_from(
        boost::asio::buffer(this->_recv_buffer),
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
        std::string str_received = std::string(reinterpret_cast<const char*>(this->_recv_buffer.data()), bytes_transferred);
        this->_all_recv.append(str_received);
        std::cout << "CLIENT -- Recu:" << this->_all_recv << std::endl;
    }
    this->startReceive();
}

std::string Client::getReponse(void)
{
    std::string str;
    auto time = timeNow;

    std::cout << "CLIENT -- reading:" << this->_all_recv << std::endl;
    while(Chrono(time) <= 5000) {
        str = this->read();
        if (str == "")
            return (str);
    }
    return (TIMEOUT_CONNECTION);
}

void Client::launch(void)
{
    boost::thread run_thread(boost::bind(&boost::asio::io_service::run, boost::ref(this->_io_service)));
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