#include "check.hpp"

namespace check
{
	bool checkNick(std::string message, User *user, Server *server)
	{
		if (message == "")
		{
			numeric::sendNumeric(ERR_NONICKNAMEGIVEN, user, server);
			return false;
		}
		if (server->getUser(message) != NULL)
		{
			numeric::sendNumeric(ERR_NICKNAMEINUSE(message), user, server);
			return false;
		}
		if (isnumber(message[0]) == 1)
		{
			numeric::sendNumeric(ERR_ERRONEUSNICKNAME(message), user, server);
			return false;
		}
		if (message.size() > 30)
		{
			numeric::sendNumeric(ERR_ERRONEUSNICKNAME(message), user, server);
			return false;
		}
		if (message.find_first_of(" \t\r\n\v\f") != std::string::npos)
		{
			numeric::sendNumeric(ERR_ERRONEUSNICKNAME(message), user, server);
			return false;
		}
		if (message.find_first_not_of(VALIDCHARS) != std::string::npos)
		{
			numeric::sendNumeric(ERR_ERRONEUSNICKNAME(message), user, server);
			return false;
		}
		return true;
	}
	bool checkUser(std::string message, User *user, Server *server)
	{
		std::string command = "USER";
		std::string modeString;
		std::string username;
		std::string hostname;
		int mode;
		int fd = user->getFd();
		try {
			username = message.substr(0, message.find(" "));
		} catch (std::exception &e){
			numeric::sendNumeric(ERR_NEEDMOREPARAMS(command), user, server);
			return false;
		}
		message = message.substr(message.find(" ") + 1);
		try {
			modeString = message.substr(0, message.find(" "));
		} catch (std::exception &e){
			numeric::sendNumeric(ERR_NEEDMOREPARAMS(command), user, server);
			return false;
		}
		try {
			mode = std::stoi(modeString);
			(void)mode;
		}
		catch (std::exception &e){
			server->sender(fd, "ERROR :Invalid mode");
			return false;
		}
		message = message.substr(message.find(" ") + 1);
		try {
			hostname = message.substr(0, message.find(" "));
		}
		catch (std::exception &e){
			numeric::sendNumeric(ERR_NEEDMOREPARAMS(command), user, server);
			return false;
		}
		message = message.substr(message.find(" ") + 1);
		try {
			message = message.substr(3);
		} catch (std::exception &e){
			numeric::sendNumeric(ERR_NEEDMOREPARAMS(command), user, server);
			return false;
		}
		user->setRealname(message);
		user->setUsername(username);
		user->setHostname(hostname);
		user->setMode(mode);
		return true;
	}
	bool checkJoin(std::string message, User *user, Server *server)
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
	bool checkPart(std::string message, User *user, Server *server)
	{
		Execute exec;
		std::string command = "PART";
		std::string partMessage = "";
		
		int fd = user->getFd();
		if (message == "")
		{
			numeric::sendNumeric(ERR_NEEDMOREPARAMS(command), user, server);
			return false;
		}
		if (message.find(",") != std::string::npos)
		{
			partMessage = " " + message.substr(message.find(":"));
			message = message.substr(0, message.find(":"));
			std::vector<std::string> channels = utils::split(message, ",");
			std::vector<std::string>::iterator it = channels.begin();
			std::vector<std::string>::iterator ite = channels.end();
			while (it != ite)
			{
				exec.execute(fd, server, "PART " + *it + partMessage);
				it++;
			}
			return false;
		}
		std::string channelName = message.substr(0, message.find(" "));
		if (server->getChannel(channelName) == NULL)
		{
			numeric::sendNumeric(ERR_NOSUCHCHANNEL(command), user, server);
			return false;
		}
		if (user->getChannel(channelName) == NULL)
		{
			numeric::sendNumeric(ERR_NOTONCHANNEL(command), user, server);
			return false;
		}
		return true;
	}
	bool checkTopic(std::string message, User *user, Server *server)
	{
		std::string command = "TOPIC";
		if (message == "")
		{
			numeric::sendNumeric(ERR_NEEDMOREPARAMS(command), user, server);
			return false;
		}
		if (message.find(" ") == std::string::npos)
		{
			numeric::sendNumeric(ERR_NEEDMOREPARAMS(command), user, server);
			return false;
		}
		std::string channelName = message.substr(0, message.find(" "));
		if (server->getChannel(channelName) == NULL)
		{
			numeric::sendNumeric(ERR_NOSUCHCHANNEL(command), user, server);
			return false;
		}
		if (user->getChannel(channelName) == NULL)
		{
			numeric::sendNumeric(ERR_NOTONCHANNEL(command), user, server);
			return false;
		}
		if (message.find(":") == std::string::npos)
		{
			numeric::sendNumeric(ERR_NEEDMOREPARAMS(command), user, server);
			return false;
		}
		return true;
	}
	bool checkKick(std::string message, User *user, Server *server)
	{
		std::string command = "KICK";
		if (message == "")
		{
			numeric::sendNumeric(ERR_NEEDMOREPARAMS(command), user, server);
			return false;
		}
		if (message.find(" ") == std::string::npos)
		{
			numeric::sendNumeric(ERR_NEEDMOREPARAMS(command), user, server);
			return false;
		}
		std::string channelName = message.substr(0, message.find(" "));
		if (server->getChannel(channelName) == NULL)
		{
			numeric::sendNumeric(ERR_NOSUCHCHANNEL(command), user, server);
			return false;
		}
		if (user->getChannel(channelName) == NULL)
		{
			numeric::sendNumeric(ERR_NOTONCHANNEL(command), user, server);
			return false;
		}
		Channel *channel = server->getChannel(channelName);
		if (channel->getOperator(user) == NULL)
		{
			numeric::sendNumeric(ERR_CHANOPRIVSNEEDED(channelName), user, server);
			return false;
		}
		std::string toKick = message.substr(message.find(" ") + 1);
		User *toKickUser = server->getUser(toKick);
		if (toKickUser == NULL)
		{
			numeric::sendNumeric(ERR_NOSUCHNICK(command), user, server);
			return false;
		}
		if (toKickUser->getChannel(channelName) == NULL)
		{
			numeric::sendNumeric(ERR_USERNOTINCHANNEL(toKick, channelName), user, server);
			return false;
		}
		if (toKickUser == channel->getOwner())
		{
			int fd = user->getFd();
			server->sender(fd, "ERROR :Cannot kick channel owner");
			return false;
		}
		return true;
	}
}