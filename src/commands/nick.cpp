#include "Execute.hpp"

void Execute::nick(int &fd, Server *server, std::string message){
	User *user = server->getUser(fd);
	if (check::checkNick(message, user, server) == false)
		return ;
	if (user->getAuth() == true)
        server->sender(fd, utils::getPrefix(user) + " NICK " + message);
	else
		user->setAuths("NICK", true);
	std::vector<Channel *> channels = user->getChannels();
	for (std::vector<Channel *>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		std::vector<User *> users = (*it)->getUsers();
		for (std::vector<User *>::iterator it2 = users.begin(); it2 != users.end(); it2++)
		{
			int toSend = (*it2)->getFd();
			if (toSend != fd)
				server->sender(toSend, utils::getPrefix(user) + " NICK " + message);
		}
	}
	user->setNickname(message);
	
}
