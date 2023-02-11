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
	this->commands.push_back(Command("USER", &Execute::user));
	//this->commands.push_back(Command("WHO", &Execute::who));
	//this->commands.push_back(Command("NOTICE", &Execute::notice));
	//this->commands.push_back(Command("MODE", &Execute::mode));
}

void Execute::join(int &fd, Server *server, std::string message){
	Channel *channel = server->getChannel(message);
	User *user = server->getUser(fd);
	if (channel == NULL){
		channel = new Channel(message);
		server->addChannel(channel);
		channel->addUser(user);
		channel->setOwner(user);
		channel->addOperator(user);
		server->sender(fd, utils::getProtocol(user) + " JOIN " + message);
	}
	else if (channel->getUser(user) == NULL)
	{
		channel->addUser(user);
		server->sender(fd, utils::getProtocol(user) + " JOIN " + message);
	}
	else
		server->sender(fd, utils::getProtocol(user) + " :You are already in this channel");
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
	if (user->getAuth() == true)
		server->sender(fd, utils::getProtocol(user) + " NICK " + message);
}

void Execute::pass(int &fd, Server *server, std::string message){
	User *user = server->getUser(fd);
	if (message[0] != ':')
	{
		server->sender(fd, "ERROR :Not enough parameters");
		return ;		
	}
	auth::authPassword(user, server, message);
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

void Execute::user(int &fd, Server *server, std::string message){
	(void)message;
	(void)server;
	(void)fd;
}

void Execute::who(int &fd, Server *server, std::string message){
	(void)message;
	(void)server;
	(void)fd;
}

void Execute::notice(int &fd, Server *server, std::string message){
	(void)message;
	(void)server;
	(void)fd;
}

void Execute::mode(int &fd, Server *server, std::string message){
	(void)message;
	(void)server;
	(void)fd;
}

std::string Execute::getCmd(std::string command){
    return command.substr(0, command.find(" "));
}

void Execute::execute(int &fd, Server *server, std::string message){
	std::string command = getCmd(message);
	User *user = server->getUser(fd);
	if (auth::checkAuth(user, server, command) == false)
		return;
	message = message.substr(message.find(" ") + 1);
	for (std::vector<Command>::iterator it = this->commands.begin(); it != this->commands.end(); it++){
		if (it->first == command){
			it->second(fd, server, message);
			return;
		}
	}
}

Execute::~Execute(){}