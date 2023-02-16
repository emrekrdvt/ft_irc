#include "Execute.hpp"

void Execute::pass(int &fd, Server *server, std::string message){
	User *user = server->getUser(fd);
	if (message[0] != ':')
	{
		numeric::sendNumeric(ERR_NEEDMOREPARAMS(message), user, server);
		return ;		
	}
	auth::authPassword(user, server, message);
}
