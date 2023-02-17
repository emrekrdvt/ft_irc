#include "Execute.hpp"

void Execute::kick(int &fd, Server *server, std::string message)
{
	User *user = server->getUser(fd);
	if (check::checkKick(message, user, server) == false)
		return ;
	std::string channelName = message.substr(0, message.find(" "));
	std::string toKick = message.substr(message.find(" ") + 1);
	Channel *channel = server->getChannel(channelName);
	User *userToKick = channel->getUser(toKick);
	std::vector<User*> users = channel->getUsers();
	for (std::vector<User*>::iterator it = users.begin(); it != users.end(); it++)
	{
		int toSend = (*it)->getFd();
		server->sender(toSend, utils::getPrefix(user) + " KICK " + channelName + " " + toKick);
	}
	channel->removeUser(userToKick);
	userToKick->removeChannel(channel);
	channel->removeOperator(userToKick);
}
