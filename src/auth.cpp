#include "auth.hpp"

namespace auth
{
	void authPassword(User *user, Server *server, std::string password)
	{
		std::string pass = ":" + server->getPassword();
		if (password == pass)
			user->setAuths("PASS", true);
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
		if (user->checkAuths() == true)
		{
			user->setAuth(true);
			std::string nickname = user->getNickname();
			std::string username = user->getUsername();
			std::string hostname = server->getHostname();
			std::string time = server->getCreatedTime();
			numeric::sendNumeric(RPL_WELCOME(nickname, username, hostname), user, server);
			numeric::sendNumeric(RPL_YOURHOST(nickname, hostname), user, server);
			numeric::sendNumeric(RPL_CREATED(nickname, time), user, server);
		}
	}
	bool checkAuth(User *user, Server *server, std::string command)
	{
		int fd = user->getFd();
		if (user->getAuth() == false && command != "PASS" && command != "USER" && command != "NICK" && command != "PING" && command != "CAP")
		{
			numeric::sendNumeric(ERR_NOTREGISTERED, user, server);
			Auth *auths = user->getAuths();
			for (int i = 0; i < 3; i++)
			{
				if (auths[i].second == false)
				{
					server->sender(fd, "ERROR :You must send " + auths[i].first + " before sending any command");
					return false;
				}
			}
			return false;
		}
		if (user->getAuth() == true && (command == "PASS" || command == "USER"))
		{
			numeric::sendNumeric(ERR_ALREADYREGISTRED, user, server);
			return false;
		}
		return true;
	}
}
