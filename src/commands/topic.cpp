#include "Execute.hpp"

void Execute::topic(int &fd, Server *server, std::string message)
{
	User *user = server->getUser(fd);
	if (check::checkTopic(message, user, server) == false)
		return ;
	std::string channelName = message.substr(0, message.find(" "));
	std::string topic = message.substr(message.find(":") + 1);
	Channel *channel = server->getChannel(channelName);
	channel->setTopic(topic);
	server->sender(fd, utils::getPrefix(user) + " TOPIC " + channelName + " :" + topic);
	std::vector<User*> users = channel->getUsers();
	for (std::vector<User*>::iterator it = users.begin(); it != users.end(); it++)
	{
		int toSend = (*it)->getFd();
		if (toSend != fd)
			server->sender(toSend, utils::getPrefix(user) + " TOPIC " + channelName + " :" + topic);
	}
	if (topic == "")
		numeric::sendNumeric(RPL_NOTOPIC(user->getNickname(), channelName), user, server);
	else
		numeric::sendNumeric(RPL_TOPIC(user->getNickname(), channelName, topic), user, server);
}
