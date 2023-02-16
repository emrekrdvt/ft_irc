#include "Server.hpp"
#include "Execute.hpp"

Execute::Execute(){
    this->commands.push_back(Command("JOIN", &Execute::join));
    this->commands.push_back(Command("PART", &Execute::part));
    this->commands.push_back(Command("PRIVMSG", &Execute::privmsg));
    this->commands.push_back(Command("QUIT", &Execute::quit));
	this->commands.push_back(Command("NICK", &Execute::nick));
	this->commands.push_back(Command("KICK", &Execute::kick));
	this->commands.push_back(Command("PASS", &Execute::pass));
	this->commands.push_back(Command("USER", &Execute::user));
	this->commands.push_back(Command("CAP", &Execute::cap));
	this->commands.push_back(Command("NOTICE", &Execute::notice));
	this->commands.push_back(Command("TOPIC", &Execute::topic));
	//this->commands.push_back(Command("WHO", &Execute::who));
	//this->commands.push_back(Command("WHOIS", &Execute::whois))
	//this->commands.push_back(Command("LIST", &Execute::list));
	//this->commands.push_back(Command("NAMES", &Execute::names));
	//this->commands.push_back(Command("VERSION", &Execute::version));
	//this->commands.push_back(Command("MOTD", &Execute::motd));
	//this->commands.push_back(Command("TIME", &Execute::time));
	//this->commands.push_back(Command("INFO", &Execute::info));
	//this->commands.push_back(Command("OPER", &Execute::oper));
}

void Execute::who(int &fd, Server *server, std::string message){
	(void)message;
	(void)server;
	(void)fd;
}

std::string Execute::getCmd(std::string command){
    return command.substr(0, command.find(" "));
}

void Execute::execute(int &fd, Server *server, std::string message){
	std::string command = getCmd(message);
	if (message.find(" ") == std::string::npos)
		message = "";
	else
		message = message.substr(message.find(" ") + 1);
	User *user = server->getUser(fd);
	if (auth::checkAuth(user, server, command) == false)
		return;
	for (std::vector<Command>::iterator it = this->commands.begin(); it != this->commands.end(); it++){
		if (it->first == command){
			it->second(fd, server, message);
			return;
		}
	}
}

Execute::~Execute(){}