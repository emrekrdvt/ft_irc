#include "numeric.hpp"

Numeric makeNumeric(std::string code, std::string message)
{
	Numeric numeric;

	numeric.first = code;
	numeric.second = message;
	return (numeric);
}

namespace numeric
{
	void sendNumeric(Numeric reply, User *user, Server *server)
	{
		int fd = user->getFd();
		std::string replyString = ":" + server->getHostname() + " " + reply.first + " " + user->getNickname() + " " + reply.second;
		server->sender(fd, replyString);
		std::cout << replyString << std::endl;
	}
}