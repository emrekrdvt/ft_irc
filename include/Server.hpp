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
#include "auth.hpp"
#include "Execute.hpp"
#include "Channel.hpp"
#include <unistd.h>

class User;
class Channel;

class Server
{
	private:
		const int max_users;
		const int port;
		std::string server_pass;
		int sockfd;
		std::vector<User*> users;
		std::vector<Channel*> channels;
		std::string hostname;
	public:
		Server(int port, std::string pass);
		~Server();
		std::vector<User*> getUsers();
		void handle_buffer(int &fd);
		int sender(int &fd, std::string msg);
		void run();
		User* getUser(int fd);
		User *getUser(std::string nickname);
		Channel *getChannel(std::string name);
		void addChannel(Channel *channel);
		void removeChannel(Channel *channel);
        std::string getPassword();
		std::string trimBuffer(std::string buffer);
		void removeUser(User *user);
		std::vector<Channel*> getChannels();
		std::string getHostname();
		void setHostname();
};


#endif