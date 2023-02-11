#include "check.hpp"

namespace check
{
	void error(std::string msg, int exitCode)
	{
		std::cerr << "Error: " << msg << std::endl;
		std::cerr << "Exiting with code " << exitCode << std::endl;
		exit(exitCode);
	}
	void checkSocket(int sock, std::string function, int exitCode)
	{
		if (sock == -1)
			error(function + "() didn't work as excepted", exitCode);
	}
	void checkRecv(int fd, char *buffer, int size)
	{
		if (recv(fd, buffer, size, 0) < 0) {
			if (errno != EWOULDBLOCK)
				error("recv() didn't work as excepted", RECVERROR);
		}
	}
	void checkArgs(int argc, char *argv[])
	{
		std::string usage = "Usage: " + std::string(argv[0]) + " <port> <password>";
		if (argc != 3)
			error(usage , USAGEERROR);
		try {
			int port = std::stoi(argv[1]);
			if (port < 1024 || port > 65535)
				error("Port must be between 1024 and 65535", PORTERROR);
		} catch (std::exception &e) {
			error("Port must be a number", PORTNUMBERERROR);
		}
	}
	bool checkNick(User *user, std::string nickname, Server *server)
	{
		if (nickname == "")
		{
			utils::err(ERR_NONICKNAMEGIVEN, user, server);
			return false;
		}
		if (server->getUser(nickname) != NULL)
		{
			utils::err(ERR_NICKNAMEINUSE(nickname), user, server);
			return false;
		}
		if (isnumber(nickname[0]) == 1)
		{
			utils::err(ERR_ERRONEUSNICKNAME(nickname), user, server);
			return false;
		}
		if (nickname.size() > 30)
		{
			utils::err(ERR_ERRONEUSNICKNAME(nickname), user, server);
			return false;
		}
		if (nickname.find_first_of(" \t\r\n\v\f") != std::string::npos)
		{
			utils::err(ERR_ERRONEUSNICKNAME(nickname), user, server);
			return false;
		}
		if (nickname.find_first_not_of(VALIDCHARS) != std::string::npos)
		{
			utils::err(ERR_ERRONEUSNICKNAME(nickname), user, server);
			return false;
		}
		return true;
	}
}