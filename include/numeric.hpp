#ifndef NUMERIC_HPP
# define NUMERIC_HPP

#include <iostream>
#include "User.hpp"
#include "Server.hpp"

class Server;
class User;

typedef std::pair<std::string, std::string> Numeric;

//RPL
#define RPL_WELCOME(nick, user, host) numeric::makeNumeric("001", ":Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host)
#define RPL_YOURHOST(nick, host) numeric::makeNumeric("002", ":Your host is " + host + ", running version ircd-irc2")

//ERR
#define ERR_ERRONEUSNICKNAME(nick) numeric::makeNumeric("432", nick + " :Erroneus nickname")
#define ERR_NICKNAMEINUSE(nick) numeric::makeNumeric("433", nick + " :Nickname is already in use")
#define ERR_NEEDMOREPARAMS(cmd) numeric::makeNumeric("461", cmd + " :Not enough parameters")
#define ERR_ALREADYREGISTRED numeric::makeNumeric("462", ":Unauthorized command (already registered)")
#define ERR_PASSWDMISMATCH numeric::makeNumeric("464", ":Password incorrect")
#define ERR_UNKNOWNCOMMAND(cmd) numeric::makeNumeric("421", cmd + " :Unknown command")
#define ERR_NOTREGISTERED numeric::makeNumeric("451", ":You have not registered")
#define ERR_NONICKNAMEGIVEN numeric::makeNumeric("431", ":No nickname given")

namespace numeric
{
	Numeric makeNumeric(std::string code, std::string message);
	void sendNumeric(Numeric reply, User *user, Server *server);
}

#endif