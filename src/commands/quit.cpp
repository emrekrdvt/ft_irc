#include "Execute.hpp"

void Execute::quit(int &fd, Server *server, std::string message){
	Execute exec;
	std::string quitMessage = message.substr(message.find(":") + 1);
	User *user = server->getUser(fd);
	std::vector<Channel*> channels = user->getChannels();
	for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		Channel *channel = *it;
		exec.execute(fd, server, "PRIVMSG " + channel->getName() + " :" + quitMessage);
	}
	if (user->getAuth() == true)
		exec.execute(fd, server, "JOIN #0");
	server->removeUser(user);
	delete user;
}
