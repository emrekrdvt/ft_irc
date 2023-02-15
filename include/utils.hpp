#ifndef UTILS_HPP
# define UTILS_HPP

#include <iostream>
#include <vector>
#include "User.hpp"
#include "Server.hpp"
#include <iomanip>

class Server;
class User;

//COLORS
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define DEFAULT "\033[0m"

namespace utils
{
	std::string trimBuffer(std::string buffer);
	std::vector<std::string> split(std::string str, std::string delim);
	void printClient(std::string msg, int fd, Server *server);
	void printServer(std::string msg, Server *server);
	std::string getPrefix(User *user);
	std::string getTime();
	std::string getColor(int fd);
}

#endif