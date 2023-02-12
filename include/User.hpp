#ifndef USER_HPP
# define USER_HPP

# include <iostream>

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
	public:
		User();
		User(int fd);
		~User();
		std::string getUsername();
		std::string getNickname();
		void setUsername(std::string username);
		void setNickname(std::string nickname);
		void setHostname(std::string hostname);
		std::string getRealname();
		void setRealname(std::string realname);
		std::string getHostname();
		void setFd(int fd);
		int getFd();
		bool getAuth();
		int getMode();
		void setAuth(bool auth);
		void setMode(int mode);
};

#endif