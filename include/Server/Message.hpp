/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Message
*/

#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

#include <string>

static const int MSG_MAX_LEN = 1024;

static const std::string TIMEOUT_CONNECTION = "##408##";
static const std::string ACCEPTED_CONNECTION = "##201##";
static const std::string INCOMMING_CONNECTION = "##100##";

class Message {
public:
    Message();
    ~Message();

protected:
private:
};

#endif /* !MESSAGE_HPP_ */
