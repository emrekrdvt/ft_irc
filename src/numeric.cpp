#include "numeric.hpp"

namespace numeric
{
	Numeric makeNumeric(std::string code, std::string message)
	{
		Numeric numeric;

		numeric.first = code;
		numeric.second = message;
		return (numeric);
	}
	void sendNumeric(Numeric reply, User *user, Server *server)
	{
		int fd = user->getFd();
		server->sender(fd, ":" + server->getHostname() + " " + reply.first + " " + user->getNickname() + " " + reply.second);
		utils::printServer(server->getHostname() + " " + reply.first + " " + user->getNickname(), server);
	}
}