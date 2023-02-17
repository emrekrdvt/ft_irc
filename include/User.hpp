#ifndef USER_HPP
# define USER_HPP

# include "Channel.hpp"
# include <iostream>
# include <vector>

class Channel;

typedef std::pair<std::string, bool> Auth;

class User
{
	private:
		std::string username;
		std::string nickname;
		std::string hostname;
		std::string realname;
		std::string message;
		int	fd;
		int mode;
		bool auth;
		bool cap;
		Auth auths[3];
		std::vector<Channel *> channels;
	public:
		User();
		User(int fd);
		~User();
		std::string getUsername();
		std::string getNickname();
		std::string getRealname();
		std::string getHostname();
		int getFd();
		bool getAuth();
		int getMode();
		bool getCap();
		
		std::vector<Channel *> getChannels();
		void setUsername(std::string username);
		void setNickname(std::string nickname);
		std::string &getmessage( void );
		void setHostname(std::string hostname);
		void setmessage( std::string message );
		void setRealname(std::string realname);
		void setFd(int fd);
		void setAuth(bool auth);
		void setMode(int mode);
		void setCap(bool cap);
		void setAuths(std::string command, bool auth);
		Auth *getAuths();
		bool checkAuths();
		void addChannel(Channel *channel);
		void removeChannel(Channel *channel);
		Channel *getChannel(std::string name);
};

#endif