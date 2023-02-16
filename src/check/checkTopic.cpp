#include "check.hpp"

bool check::checkTopic(std::string message, User *user, Server *server)
{
	std::string command = "TOPIC";
	if (message == "")
	{
		numeric::sendNumeric(ERR_NEEDMOREPARAMS(command), user, server);
		return false;
	}
	if (message.find(" ") == std::string::npos)
	{
		numeric::sendNumeric(ERR_NEEDMOREPARAMS(command), user, server);
		return false;
	}
	std::string channelName = message.substr(0, message.find(" "));
	if (server->getChannel(channelName) == NULL)
	{
		numeric::sendNumeric(ERR_NOSUCHCHANNEL(command), user, server);
		return false;
	}
	if (user->getChannel(channelName) == NULL)
	{
		numeric::sendNumeric(ERR_NOTONCHANNEL(command), user, server);
		return false;
	}
	if (message.find(":") == std::string::npos)
	{
		numeric::sendNumeric(ERR_NEEDMOREPARAMS(command), user, server);
		return false;
	}
	return true;
}
