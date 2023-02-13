#ifndef UTILS_HPP
# define UTILS_HPP

#include <iostream>
#include <vector>
#include "User.hpp"
#include "Server.hpp"

class Server;

namespace utils
{
	std::string trimBuffer(std::string buffer);
	std::vector<std::string> split(std::string str, std::string delim);
	void printClient(std::string msg, int fd, Server *server);
	std::string getPrefix(User *user);
}

#endif