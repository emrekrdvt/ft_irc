#include "utils.hpp"

namespace utils
{
	std::string trimBuffer(std::string buffer)
	{
		std::string trimmed = buffer;
		trimmed.erase(trimmed.find_last_not_of("\r\n") + 1);
		return trimmed;
	}
	std::vector<std::string> split(std::string str, std::string delim)
	{
		std::vector<std::string> result;
		size_t pos = 0;
		std::string token;
		while ((pos = str.find(delim)) != std::string::npos)
		{
			token = str.substr(0, pos);
			result.push_back(token);
			str.erase(0, pos + delim.length());
		}
		result.push_back(str);
		return result;
	}
	void printClient(std::string msg, int fd, Server *server)
	{
		User *user = server->getUser(fd);
		if (user->getAuth() == false)
			std::cout << "[Client " << fd << "]\n" << " " + msg << std::endl;
		else
		{
			std::cout << "----------------------------------------" << std::endl;
			std::cout << "[Client " << fd << "]" << std::endl;
			std::cout << " Nickname: " << user->getNickname() << std::endl;
			std::cout << " Username: " << user->getUsername() << std::endl;
			std::cout << " Realname: " << user->getRealname() << std::endl;
			std::cout << " Hostname: " << user->getHostname() << std::endl;
			std::cout << " Message: " << msg << std::endl;
			std::cout << "----------------------------------------" << std::endl;
		}
	}
	std::string getPrefix(User *user)
	{
		return ":" + user->getNickname() + "!" + user->getUsername() + "@" + user->getHostname();
	}
}