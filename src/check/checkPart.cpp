#include "check.hpp"

bool check::checkPart(std::string message, User *user, Server *server)
{
	Execute exec;
	std::string command = "PART";
	std::string partMessage = "";
	
	int fd = user->getFd();
	if (message == "")
	{
		numeric::sendNumeric(ERR_NEEDMOREPARAMS(command), user, server);
		return false;
	}
	if (message.find(",") != std::string::npos)
	{
		partMessage = " " + message.substr(message.find(":"));
		message = message.substr(0, message.find(":"));
		std::vector<std::string> channels = utils::split(message, ",");
		std::vector<std::string>::iterator it = channels.begin();
		std::vector<std::string>::iterator ite = channels.end();
		while (it != ite)
		{
			exec.execute(fd, server, "PART " + *it + partMessage);
			it++;
		}
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
	return true;
}
