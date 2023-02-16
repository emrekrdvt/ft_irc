#include "Execute.hpp"

void Execute::part(int &fd, Server *server, std::string message){
	Execute exec;
	User *user = server->getUser(fd);
	std::string msg = "";
	if (check::checkPart(message, user, server) == false)
		return ;
	std::string channelName = message.substr(0, message.find(" "));
	if (message.find(":") != std::string::npos)
		msg = message.substr(message.find(":") + 1);
	Channel *channel = server->getChannel(channelName);
	if (user == channel->getOwner())
		channel->cedeOwnership(server);
	channel->removeUser(user);
	user->removeChannel(channel);
	channel->removeOperator(user);
	if (msg != "")
		exec.execute(fd, server, "PRIVMSG " + channelName + " :" + msg);
	server->sender(fd, utils::getPrefix(user) + " PART " + channelName);
	std::vector<User*> users = channel->getUsers();
	for (std::vector<User*>::iterator it = users.begin(); it != users.end(); it++)
	{
		int toSend = (*it)->getFd();
		server->sender(toSend, utils::getPrefix(user) + " PART " + channelName);
	}
	if (channel->getUsers().size() == 0)
	{
		server->removeChannel(channel);
		delete channel;
		return ;
	}
	User *bot = channel->getUser("bot");
	if (channel->getUsers().size() == 1 && bot != NULL)
	{
		int botFd = bot->getFd();
		server->sender(botFd, utils::getPrefix(bot) + " PART " + channelName);
		channel->removeUser(bot);
		bot->removeChannel(channel);
		channel->removeOperator(bot);
		delete channel;
	}
}
