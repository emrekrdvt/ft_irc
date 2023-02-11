#ifndef UTILS_HPP
# define UTILS_HPP

#include <iostream>
#include <vector>
#include "User.hpp"
#include "Server.hpp"

class Server;

typedef std::pair<std::string, int> Numeric;

Numeric makeNumeric(int code, std::string message);

#define ERR_ERRONEUSNICKNAME(nick) makeNumeric(432, nick + " :Erroneus nickname")
#define ERR_NICKNAMEINUSE(nick) makeNumeric(433, nick + " :Nickname is already in use")
#define ERR_NEEDMOREPARAMS(cmd) makeNumeric(461, cmd + " :Not enough parameters")
#define ERR_ALREADYREGISTRED makeNumeric(462, ":Unauthorized command (already registered)")
#define ERR_PASSWDMISMATCH makeNumeric(464, ":Password incorrect")
#define ERR_UNKNOWNCOMMAND(cmd) makeNumeric(421, cmd + " :Unknown command")
#define ERR_NOTREGISTERED makeNumeric(451, ":You have not registered")
#define ERR_NONICKNAMEGIVEN makeNumeric(431, ":No nickname given")

namespace utils
{
	std::string trimBuffer(std::string buffer);
	std::vector<std::string> split(std::string str, std::string delim);
	void printClient(std::string msg, int fd);
	std::string getProtocol(User *user);
	void err(Numeric numeric, User *user, Server *server);
}

#endif