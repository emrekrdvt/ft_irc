#include "auth.hpp"

namespace auth
{
	void authPassword(User *user, Server *server, std::string password)
	{
		std::string pass = ":" + server->getPassword();
		if (password == pass)
			user->setAuth(true);
		else
			utils::err(ERR_PASSWDMISMATCH, user, server);
	}
	void handleAuth(User *user, Execute exec, std::string message, Server *server)
	{
		int fd = user->getFd();
		std::vector<std::string> split_message = utils::split(message, "\n");
		std::vector<std::string>::iterator it = split_message.begin();
		std::vector<std::string>::iterator ite = split_message.end();
		while (it != ite)
		{
			message = utils::trimBuffer(*it);
			exec.execute(fd, server, message);
			it++;
		}
		if (user->getAuth() == true)
			server->sender(fd, ":ircserv 001 " + user->getNickname() + " :Welcome to the Internet Relay Network ");
	}
	bool checkAuth(User *user, Server *server, std::string command)
	{
		if (user->getAuth() == false && command != "PASS" && command != "USER" && command != "NICK")
		{
			utils::err(ERR_NOTREGISTERED, user, server);
			return false;
		}
		if (user->getAuth() == true && command == "PASS")
		{
			utils::err(ERR_ALREADYREGISTRED, user, server);
			return false;
		}
		return true;
	}
}
