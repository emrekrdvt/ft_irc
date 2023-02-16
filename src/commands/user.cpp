#include "Execute.hpp"

void Execute::user(int &fd, Server *server, std::string message){
	User *user = server->getUser(fd);
	if (check::checkUser(message, user, server) == false)
		return ;
	user->setAuths("USER", true);
}
