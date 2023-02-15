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
	this->commands.push_back(Command("CAP", &Execute::cap));
	this->commands.push_back(Command("NOTICE", &Execute::notice));
	//this->commands.push_back(Command("WHO", &Execute::who));
	//this->commands.push_back(Command("MODE", &Execute::mode));
	//this->commands.push_back(Command("LIST", &Execute::list));
	//this->commands.push_back(Command("TOPIC", &Execute::topic));
}

void Execute::join(int &fd, Server *server, std::string message){
	Channel *channel = server->getChannel(message);
	User *user = server->getUser(fd);
	if (check::checkJoin(message, user, server) == false)
		return ;
	if (channel == NULL){
		channel = new Channel(message);
		server->addChannel(channel);
		channel->addUser(user);
		channel->setOwner(user);
		channel->addOperator(user);
		server->sender(fd, utils::getPrefix(user) + " JOIN " + message);
		server->sender(fd, utils::getPrefix(user) + " MODE " + message + " +o " + user->getNickname());
		user->addChannel(channel);
		return ;
	}
	if (channel->getUser(user) == NULL)
	{
		server->sender(fd, utils::getPrefix(user) + " JOIN " + message);
		channel->addUser(user);
		user->addChannel(channel);
	}
	std::string nicknames = "";
	std::string nickname = user->getNickname();	
	std::string channelName = channel->getName();
	std::vector<User *> users = channel->getUsers();
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++)
	{
		int toSend = (*it)->getFd();
		if (toSend != fd)
			server->sender(toSend, utils::getPrefix(user) + " JOIN " + message);
		if (it != users.begin())
			nicknames += " ";
		if (channel->getOperator((*it)) != NULL)
			nicknames += "@";
		nicknames += (*it)->getNickname();
	}
	numeric::sendNumeric(RPL_NAMEREPLY(nickname, channelName, nicknames), user, server);
	numeric::sendNumeric(RPL_ENDOFNAMES(nickname, channelName), user, server);
}

void Execute::part(int &fd, Server *server, std::string message){
	Execute exec;
	std::string channelName = message.substr(0, message.find(" "));
	std::string msg = message.substr(message.find(":") + 1);
	Channel *channel = server->getChannel(channelName);
	User *user = server->getUser(fd);
	if (check::checkPart(channelName, user, server) == false)
		return ;
	channel->removeUser(user);
	user->removeChannel(channel);
	exec.execute(fd, server, "PRIVMSG " + channelName + " :" + msg);
	server->sender(fd, utils::getPrefix(user) + " PART " + channelName);
	std::vector<User*> users = channel->getUsers();
	for (std::vector<User*>::iterator it = users.begin(); it != users.end(); it++)
	{
		int toSend = (*it)->getFd();
		server->sender(toSend, utils::getPrefix(user) + " PART " + channelName);
	}
	if (channel->getUsers().size() == 0)
	{
		server->removeChannel(channel);
		delete channel;
	}
}

void Execute::privmsg(int &fd, Server *server, std::string message){
	std::string toWho = message.substr(0, message.find(" "));
	std::string msg = message.substr(message.find(" ") + 1);
	User *user = server->getUser(fd);

	if (toWho[0] == '#')
	{
		
		std::string channelName = toWho;
		Channel *channel = server->getChannel(channelName);
		if (channel == NULL)
		{
			server->sender(fd, "ERROR :No such channel");
			return ;
		}
		std::vector<User*> users = channel->getUsers();
		for (std::vector<User*>::iterator it = users.begin(); it != users.end(); it++)
		{
			int fd2 = (*it)->getFd();
			User *user2 = server->getUser(fd2);
			if (user2->getFd() == fd)
				continue;
			server->sender(fd2, utils::getPrefix(user) + " PRIVMSG " + channelName + " :" + msg);
		}
	}
	else
	{

		User *user = server->getUser(toWho);
		if (user == NULL)
		{
			server->sender(fd, "ERROR :No such user");
			return ;
		}
		else
		{
			int recvFd = user->getFd();
			server->sender(recvFd, utils::getPrefix(server->getUser(fd)) + " PRIVMSG " + toWho + " :" + msg);
		}
	}
}

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

void Execute::pass(int &fd, Server *server, std::string message){
	User *user = server->getUser(fd);
	if (message[0] != ':')
	{
		numeric::sendNumeric(ERR_NEEDMOREPARAMS(message), user, server);
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
	User *user = server->getUser(fd);
	if (check::checkUser(message, user, server) == false)
		return ;
	user->setAuths("USER", true);
}

void Execute::who(int &fd, Server *server, std::string message){
	(void)message;
	(void)server;
	(void)fd;
}

void Execute::notice(int &fd, Server *server, std::string message){
	std::string toWho = message.substr(0, message.find(" "));
	std::string msg = message.substr(message.find(" ") + 1);

	int recvFd = server->getUser(toWho)->getFd();

	std::vector<Channel *> channels = server->getChannels();
	std::vector<Channel *>::iterator it = channels.begin();
	for (; it != channels.end(); it++)
	{
		std::vector<User *> users = (*it)->getUsers();
		std::vector<User *>::iterator it2 = users.begin();
		for (; it2 != users.end(); it2++)
		{
			if ((*it2)->getFd() == fd)
			{
				std::string channelName = (*it)->getName();
				std::string nickname = (*it2)->getNickname();
				server->sender(recvFd, utils::getPrefix(server->getUser(fd)) + " NOTICE " + channelName + " :" + msg);
			}
		}
	}
}

void Execute::mode(int &fd, Server *server, std::string message){
	(void)message;
	(void)server;
	(void)fd;
}

void Execute::cap(int &fd, Server *server, std::string message){
	static bool check;
	(void)message;
	if (check == false)
	{
		server->sender(fd, "CAP * LS :multi-prefix sasl");
		check = true;
	}
	else
	{
		server->sender(fd, "CAP * ACK multi-prefix");
		check = false;
	}
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