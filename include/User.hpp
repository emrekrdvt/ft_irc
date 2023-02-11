#ifndef USER_HPP
# define USER_HPP

# include <iostream>

class User
{
	private:
		std::string username;
		std::string nickname;
		int	fd;
		bool auth;
	public:
		User();
		User(int fd);
		~User();
		std::string getUsername();
		std::string getNickname();
		void setUsername(std::string username);
		void setNickname(std::string nickname);
		void setFd(int fd);
		int getFd();
		bool getAuth();
		void setAuth(bool auth);
};

#endif