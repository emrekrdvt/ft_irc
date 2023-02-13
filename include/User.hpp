#ifndef USER_HPP
# define USER_HPP

# include <iostream>

typedef std::pair<std::string, bool> Auth;

class User
{
	private:
		std::string username;
		std::string nickname;
		std::string hostname;
		std::string realname;
		int	fd;
		bool auth;
		int mode;
		Auth auths[3];
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
		void setUsername(std::string username);
		void setNickname(std::string nickname);
		void setHostname(std::string hostname);
		void setRealname(std::string realname);
		void setFd(int fd);
		void setAuth(bool auth);
		void setMode(int mode);
		void setAuths(std::string command, bool auth);
		Auth *getAuths();
		bool checkAuths();
};

#endif