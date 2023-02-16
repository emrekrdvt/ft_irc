#include "Execute.hpp"

void Execute::join(int &fd, Server *server, std::string message){
	Channel *channel = server->getChannel(message);
	User *user = server->getUser(fd);
	if (check::checkJoin(message, user, server) == false)
		return ;
	if (channel == NULL){
		channel = new Channel(message);
		server->addChannel(channel);
		channel->addUser(user);
		channel->setOwner(user);
		channel->addOperator(user);
		server->sender(fd, utils::getPrefix(user) + " JOIN " + message);
		server->sender(fd, utils::getPrefix(user) + " MODE " + message + " +o " + user->getNickname());
		user->addChannel(channel);
		numeric::sendNumeric(RPL_NOTOPIC(user->getNickname(), message), user, server);
		return ;
	}
	if (channel->getUser(user) == NULL)
	{
		server->sender(fd, utils::getPrefix(user) + " JOIN " + message);
		channel->addUser(user);
		user->addChannel(channel);
		if (channel->getTopic() != "")	
			numeric::sendNumeric(RPL_TOPIC(user->getNickname(), message, channel->getTopic()), user, server);
		else
			numeric::sendNumeric(RPL_NOTOPIC(user->getNickname(), message), user, server);
	}
	std::string nicknames = "";
	std::string nickname = user->getNickname();	
	std::string channelName = channel->getName();
	std::vector<User *> users = channel->getUsers();
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++)
	{
		int toSend = (*it)->getFd();
		if (toSend != fd)
			server->sender(toSend, utils::getPrefix(user) + " JOIN " + message);
		if (it != users.begin())
			nicknames += " ";
		if (channel->getOperator((*it)) != NULL)
			nicknames += "@";
		nicknames += (*it)->getNickname();
	}
	numeric::sendNumeric(RPL_NAMEREPLY(nickname, channelName, nicknames), user, server);
	numeric::sendNumeric(RPL_ENDOFNAMES(nickname, channelName), user, server);
}
