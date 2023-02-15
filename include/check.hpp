#ifndef CHECK_HPP
# define CHECK_HPP

#include <iostream>
#include "Server.hpp"
#include "User.hpp"
#include "Execute.hpp"

#define VALIDCHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]\\`_^{|}-"

class Server;
class User;

namespace check
{
	bool checkNick(std::string message, User *user, Server *server);
	bool checkUser(std::string message, User *user, Server *server);
	bool checkJoin(std::string message, User *user, Server *server);
	bool checkPart(std::string message, User *user, Server *server);
	bool checkTopic(std::string message, User *user, Server *server);
	bool checkKick(std::string message, User *user, Server *server);
}

#endif