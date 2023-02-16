#include "check.hpp"

bool check::checkUser(std::string message, User *user, Server *server)
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
