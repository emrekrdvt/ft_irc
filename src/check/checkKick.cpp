#include "check.hpp"

bool check::checkKick(std::string message, User *user, Server *server)
{
	std::string command = "KICK";
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
	Channel *channel = server->getChannel(channelName);
	if (channel->getOperator(user) == NULL && channel->getOwner() != user)
	{
		numeric::sendNumeric(ERR_CHANOPRIVSNEEDED(channelName), user, server);
		return false;
	}
	std::string toKick = message.substr(message.find(" ") + 1);
	User *toKickUser = server->getUser(toKick);
	if (toKickUser == NULL)
	{
		numeric::sendNumeric(ERR_NOSUCHNICK(command), user, server);
		return false;
	}
	if (toKickUser->getChannel(channelName) == NULL)
	{
		numeric::sendNumeric(ERR_USERNOTINCHANNEL(toKick, channelName), user, server);
		return false;
	}
	if (toKickUser == channel->getOwner())
	{
		int fd = user->getFd();
		server->sender(fd, "ERROR :Cannot kick channel owner");
		return false;
	}
	return true;
}
