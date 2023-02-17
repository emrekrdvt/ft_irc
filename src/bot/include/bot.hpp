#ifndef BOT_HPP
#define BOT_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <cstring>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <algorithm>

#include "roll.hpp"
#include "utils.hpp"


class bot
{
    private:
        int					_port;
		std::string			_password;
        std::string         _host;
		int					_serverfd;
		struct sockaddr_in	_address;
		bool				_connected;
        std::string         _mynick;
        std::string         _hostname;
    public:
        bot(std::string host, int port, std::string password);
        ~bot();
        void run_bot(void);
        bool send_message(std::string message);
        void processData(std::string data);
        bool command_handler(std::string nick, std::string command, std::string message);
        bool send_message_to_channel(std::string channel, std::string command);
        std::string getHostname();
};


#endif