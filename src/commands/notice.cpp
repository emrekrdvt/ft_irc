#include "Execute.hpp"

void Execute::notice(int &fd, Server *server, std::string message){
	std::string toWho = message.substr(0, message.find(" "));
	std::string msg = message.substr(message.find(" ") + 1);

	int recvFd = server->getUser(toWho)->getFd();

	std::vector<Channel *> channels = server->getChannels();
	std::vector<Channel *>::iterator it = channels.begin();
	for (; it != channels.end(); it++)
	{
		std::vector<User *> users = (*it)->getUsers();
		std::vector<User *>::iterator it2 = users.begin();
		for (; it2 != users.end(); it2++)
		{
			if ((*it2)->getFd() == fd)
			{
				std::string channelName = (*it)->getName();
				std::string nickname = (*it2)->getNickname();
				server->sender(recvFd, utils::getPrefix(server->getUser(fd)) + " NOTICE " + channelName + " :" + msg);
			}
		}
	}
}
