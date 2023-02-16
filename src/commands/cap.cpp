#include "Execute.hpp"

void Execute::cap(int &fd, Server *server, std::string message){
	User *user = server->getUser(fd);
	(void)message;
	if (user->getCap() == false)
	{
		server->sender(fd, "CAP * LS :multi-prefix sasl");
		user->setCap(true);
	}
	else
	{
		server->sender(fd, "CAP * ACK multi-prefix");
		user->setCap(false);
	}
}
