#include "Execute.hpp"

void Execute::privmsg(int &fd, Server *server, std::string message){
	std::string toWho = message.substr(0, message.find(" "));
	std::string msg = message.substr(message.find(" ") + 1);
	User *user = server->getUser(fd);

	if (toWho[0] == '#')
	{
		
		std::string channelName = toWho;
		Channel *channel = server->getChannel(channelName);
		if (channel == NULL)
		{
			numeric::sendNumeric(ERR_NOSUCHCHANNEL(channelName), user, server);
			return ;
		}
		std::vector<User*> users = channel->getUsers();
		for (std::vector<User*>::iterator it = users.begin(); it != users.end(); it++)
		{
			int fd2 = (*it)->getFd();
			User *user2 = server->getUser(fd2);
			if (user2->getFd() == fd)
				continue;
			server->sender(fd2, utils::getPrefix(user) + " PRIVMSG " + channelName + " " + msg);
		}
	}
	else
	{
		User *user = server->getUser(toWho);
		if (user == NULL)
		{
			numeric::sendNumeric(ERR_NOSUCHNICK(toWho), server->getUser(fd), server);
			return ;
		}
		else
		{
			int recvFd = user->getFd();
			server->sender(recvFd, utils::getPrefix(server->getUser(fd)) + " PRIVMSG " + toWho + " " + msg);
		}
	}
}
