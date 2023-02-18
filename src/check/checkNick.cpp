#include "check.hpp"

bool check::checkNick(std::string message, User *user, Server *server)
	{
		if (message == "")
		{
			numeric::sendNumeric(ERR_NONICKNAMEGIVEN, user, server);
			return false;
		}
		if (server->getUser(message) != NULL)
		{
			numeric::sendNumeric(ERR_NICKNAMEINUSE(message), user, server);
			return false;
		}
		if (isnumber(message[0]) == 1)
		{
			numeric::sendNumeric(ERR_ERRONEUSNICKNAME(message), user, server);
			return false;
		}
		if (message.size() > 30)
		{
			numeric::sendNumeric(ERR_ERRONEUSNICKNAME(message), user, server);
			return false;
		}
		if (message.find_first_of(" \t\r\n\v\f") != std::string::npos)
		{
			numeric::sendNumeric(ERR_ERRONEUSNICKNAME(message), user, server);
			return false;
		}
		if (message.find_first_not_of(VALIDCHARS) != std::string::npos)
		{
			numeric::sendNumeric(ERR_ERRONEUSNICKNAME(message), user, server);
			return false;
		}
		return true;
	}