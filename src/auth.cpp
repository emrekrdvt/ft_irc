#include "auth.hpp"

namespace auth
{
	void authPassword(User *user, Server *server, std::string password)
	{
		std::string pass = ":" + server->getPassword();
		if (password == pass)
			user->setAuth(true);
		else
			numeric::sendNumeric(ERR_PASSWDMISMATCH, user, server);
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
		{
			std::string nickname = user->getNickname();
			std::string username = user->getUsername();
			std::string hostname = server->getHostname();
			numeric::sendNumeric(RPL_WELCOME(nickname, username, hostname), user, server);
			numeric::sendNumeric(RPL_YOURHOST(nickname, hostname), user, server);
		}
	}
	bool checkAuth(User *user, Server *server, std::string command)
	{
		if (user->getAuth() == false && command != "PASS" && command != "USER" && command != "NICK")
		{
			numeric::sendNumeric(ERR_NOTREGISTERED, user, server);
			return false;
		}
		if (user->getAuth() == true && command == "PASS")
		{
			numeric::sendNumeric(ERR_ALREADYREGISTRED, user, server);
			return false;
		}
		return true;
	}
}
