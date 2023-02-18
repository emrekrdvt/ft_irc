#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <fcntl.h>
#include "User.hpp"
#include "error.hpp"
#include "utils.hpp"
#include "auth.hpp"
#include "Execute.hpp"
#include "Channel.hpp"
#include <unistd.h>
#include <signal.h>


class User;
class Channel;

# define VERSION "v1.0.0"
# define MAX_USERS 1000
# define MAX_BUFFER_SIZE 512

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
		std::string createdTime;
	public:
		Server(int port, std::string pass);
		~Server();
		sockaddr_in addr;
		std::vector<User*> getUsers();
		int	handle_buffer(int &fd);
		int sender(int &fd, std::string msg);
		void start();
		void run();
		User* getUser(int fd);
		User *getUser(std::string nickname);
		Channel *getChannel(std::string name);
		void addChannel(Channel *channel);
        std::string getPassword();
		std::vector<Channel*> getChannels();
		std::string getHostname();
		void setHostname();
		std::string getCreatedTime();
		void removeUser(User *user);
		void removeChannel(Channel *channel);
		int getFd();
};


#endif