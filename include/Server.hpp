#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <fcntl.h>
#include "User.hpp"
#include "check.hpp"
#include "utils.hpp"
#include "Execute.hpp"

class User;

class Server
{
	private:
		const int max_users;
		const int port;
		std::string server_pass;
		int sockfd;
		std::vector<User*> users;
	public:
		Server(int port, std::string pass);
		~Server();
		std::vector<User*> getUsers();
		void handle_buffer(int &fd);
		int sender(int &fd, std::string msg);
		void run();
		User* getUser(int fd);
		User *getUser(std::string nickname);
        std::string getPassword();
		std::string trimBuffer(std::string buffer);
		void removeUser(User *user);
		void handleAuth(User *user, std::string message);
};


#endif