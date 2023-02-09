#include "Server.hpp"
#include "Execute.hpp"

Execute::Execute(){
    this->commands.push_back(Command("JOIN", &Execute::join));
    this->commands.push_back(Command("PART", &Execute::part));
    this->commands.push_back(Command("PRIVMSG", &Execute::privmsg));
    this->commands.push_back(Command("QUIT", &Execute::quit));
    this->commands.push_back(Command("NICK", &Execute::nick));
    this->commands.push_back(Command("PING", &Execute::ping));
    this->commands.push_back(Command("KICK", &Execute::kick));
	this->commands.push_back(Command("PASS", &Execute::pass));
}

void Execute::join(int &fd, Server *server, std::string message){
	utils::printClient("JOIN " + message, fd);
	User *user = server->getUser(fd);
	server->sender(fd, user->getMsg() + " JOIN " + message);
}

void Execute::part(int &fd, Server *server, std::string message){
	(void)message;
	(void)server;
	(void)fd;
}

void Execute::privmsg(int &fd, Server *server, std::string message){
	(void)message;
	(void)server;
	(void)fd;
}

void Execute::nick(int &fd, Server *server, std::string message){
	User *user = server->getUser(fd);
	user->setNickname(message);
	utils::printClient("NICK " + message, fd);
}

void Execute::pass(int &fd, Server *server, std::string message){
	User *user = server->getUser(fd);
	check::checkPassword(user, server, message);
}

void Execute::kick(int &fd, Server *server, std::string message)
{
	(void)message;
	(void)server;
	(void)fd;
}

void Execute::quit(int &fd, Server *server, std::string message){
	(void)message;
	(void)server;
	(void)fd;
}

void Execute::ping(int &fd, Server *server, std::string message){
	(void)message;
	(void)server;
	(void)fd;
}

std::string Execute::getCmd(std::string command){
    return command.substr(0, command.find(" "));
}

void Execute::execute(int &fd, Server *server, std::string message){
	std::string command = getCmd(message);
	message = message.substr(message.find(" ") + 1);
	for (std::vector<Command>::iterator it = this->commands.begin(); it != this->commands.end(); it++){
		if (it->first == command){
			it->second(fd, server, message);
			return ;
		}
	}
}

Execute::~Execute(){
    
}