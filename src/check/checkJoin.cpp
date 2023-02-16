#include "check.hpp"

bool check::checkJoin(std::string message, User *user, Server *server)
{
	Execute exec;
	int fd = user->getFd();
	std::string command = "JOIN";
	if (message == "")
	{
		numeric::sendNumeric(ERR_NEEDMOREPARAMS(command), user, server);
		return false;
	}
	if (message.find(",") != std::string::npos)
	{
		std::vector<std::string> channels = utils::split(message, ",");
		std::vector<std::string>::iterator it = channels.begin();
		std::vector<std::string>::iterator ite = channels.end();
		while (it != ite)
		{
			std::cout << "JOIN " + *it << std::endl;
			exec.execute(fd, server, "JOIN " + *it);
			it++;
		}
		return false;
	}
	if (message == "#0")
	{
		std::vector<Channel *> channels = user->getChannels();
		std::vector<Channel *>::iterator it = channels.begin();
		std::vector<Channel *>::iterator ite = channels.end();
		while (it != ite)
		{
			exec.execute(fd, server, "PART " + (*it)->getName());
			it++;
		}
		return false;
	}
	if (message[0] != '#')
	{
		numeric::sendNumeric(ERR_NOSUCHCHANNEL(command), user, server);
		return false;
	}
	if (message.length() > 50)
	{
		numeric::sendNumeric(ERR_NOSUCHCHANNEL(command), user, server);
		return false;
	}
	if (user->getChannel(message) != NULL)
	{
		numeric::sendNumeric(ERR_USERONCHANNEL(user->getNickname(), message), user, server);
		return false;
	}
	return true;
}
