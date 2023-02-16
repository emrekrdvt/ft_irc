#include "Execute.hpp"

void Execute::nick(int &fd, Server *server, std::string message){
	User *user = server->getUser(fd);
	if (check::checkNick(message, user, server) == false)
		return ;
	if (user->getAuth() == true)
        server->sender(fd, utils::getPrefix(user) + " NICK " + message);
	else
		user->setAuths("NICK", true);
	user->setNickname(message);
}
