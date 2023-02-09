#include "Server.hpp"

Server::Server(int port, std::string pass) : max_users(32), port(port) 
{
	int rtn;
	int on = 1;
	this->server_pass = pass;
	this->sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	check::checkSocket(this->sockfd, "socket", SOCKETERROR);
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(this->port);
	rtn = bind(this->sockfd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
	check::checkSocket(rtn, "bind", BINDERROR);
	rtn = listen(this->sockfd, this->max_users);
	check::checkSocket(rtn, "listen", LISTENERROR);
	rtn = setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	check::checkSocket(rtn, "setsockopt", SETSOCKOPTERROR);
	rtn = fcntl(this->sockfd, F_SETFL, O_NONBLOCK);
	check::checkSocket(rtn, "fcntl", FCNTLERROR);
	rtn = listen(sockfd, this->max_users);
	check::checkSocket(rtn, "listen", LISTENERROR);
}	

int Server::sender(int &fd, std::string msg)
{
	std::string buffer = msg + "\r\n";
	int len = buffer.length();
	send(fd, buffer.c_str(), len, 0);
	return 1;
}

void Server::handleAuth(User *user, std::string message)
{
	int fd = user->getFd();
	std::vector <std::string> sp = utils::split(message, "\r\n");
	std::vector<std::string>::iterator it = sp.begin();
	sp.pop_back();
	while (it != sp.end())
	{
		std::vector<std::string> sp2 = utils::split(*it, " ");
		std::vector<std::string>::iterator it2 = sp2.begin();
		while (it2 != sp2.end())
		{
			if (sp2[0] == "PASS")
			{
				std::string password = ":" + this->getPassword();
				if (sp2[1] == password)
					user->setAuth(true);
				else
					this->sender(fd, "464 Password incorrect");
			}
			else if (sp2[0] == "NICK")
				user->setNickname(sp2[1]);
			else if (sp2[0] == "USER")
				user->setUsername(sp2[1]);
			it2++;
		}
		it++;
	}
	if (user->getAuth() == true)
	{
		this->sender(fd, ":ircserv 001 " + user->getNickname() + " :Welcome to the Internet Relay Network ");
	}
}

void Server::handle_buffer(int &fd)
{
	std::string message;
	Execute exec;

	char buffer[100];
	memset(buffer, 0, 100);
	while (!strstr(buffer, "\n")) 
	{
		memset(buffer, 0, 100);
		if (recv(fd, buffer, 100, 0) < 0) {
			if (errno != EWOULDBLOCK)
			{
				perror("Error");
				exit(1);
			}
		}
		message.append(buffer);
	}
	std::cout << "Message: \n" << message << std::endl;
	User *user = this->getUser(fd);
	if (user->getAuth() == false)
	{
		this->handleAuth(user, message);
		return;
	}
	message = utils::trimBuffer(message);
	exec.execute(fd, this, message);
}

void Server::run()
{
	int rtn;
	std::vector<pollfd> fds(1);
	fds[0].fd = this->sockfd;
	fds[0].events = POLLIN;
	std::cout << "Server is Running!" << std::endl;
	while (true)
	{
		int ready = poll(&fds[0], fds.size(), 1);
		check::checkSocket(ready, "poll", POLLERROR);
		if (ready == 0)
			continue;
		else
		{
			if (fds[0].revents & POLLIN)
			{
				struct sockaddr_in client_address;
				int client_sockfd = accept(this->sockfd, reinterpret_cast<sockaddr*>(&client_address), reinterpret_cast<socklen_t*>(&client_address));
				check::checkSocket(client_sockfd, "accept", ACCEPTERROR);
				rtn = fcntl(client_sockfd, F_SETFL, O_NONBLOCK);
				check::checkSocket(rtn, "fcntl", FCNTLERROR);
				pollfd temp;
				temp.fd = client_sockfd;
				temp.events = POLLIN;
				fds.push_back(temp);
				this->users.push_back(new User(temp.fd));
				utils::printClient("New client connected", temp.fd);
			}
			for (size_t i = 1; i < fds.size(); i++)
			{
				if (fds[i].revents & POLLIN)
					handle_buffer(fds[i].fd);
			}
		}
	}
	
}

Server::~Server(){}

std::vector<User*> Server::getUsers()
{
	return this->users;
}

User *Server::getUser(int fd)
{
	for (size_t i = 0; i < this->users.size(); i++)
	{
		if (this->users[i]->getFd() == fd)
			return this->users[i];
	}
	return NULL;
}

User *Server::getUser(std::string nickname)
{
	for (size_t i = 0; i < this->users.size(); i++)
	{
		if (this->users[i]->getNickname() == nickname)
			return this->users[i];
	}
	return NULL;
}

std::string Server::getPassword()
{
	return this->server_pass;
}
