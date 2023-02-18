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
		std::string color = utils::getColor(fd);
		std::cout << " ----------------------------------------" << std::endl;
		std::cout << color << " [Client " << fd << "]" << DEFAULT << std::endl;
		if (user->getAuth() == true)
		{
			std::cout << " Nickname: " << user->getNickname() << std::endl;
			std::cout << " Username: " << user->getUsername() << std::endl;
			std::cout << " Realname: " << user->getRealname() << std::endl;
			std::cout << " Hostname: " << user->getHostname() << std::endl;
		}
		std::cout << " Date: " << utils::getTime() << std::endl;
		std::cout << "\n " << MAGENTA + msg + DEFAULT  << std::endl;
		std::cout << " ----------------------------------------\n" << std::endl;
	}
	void printServer(std::string msg, Server *server)
	{
		std::cout << " ----------------------------------------" << std::endl;
		std::cout << GREEN << " [Server " << server->getHostname() << "]"  << DEFAULT << std::endl;
		std::cout << " Created: " << server->getCreatedTime() << std::endl;
		std::cout << " Version: " << VERSION << std::endl;
		std::cout << "\n " << MAGENTA + msg  + DEFAULT << std::endl;
		std::cout << " ----------------------------------------\n" << std::endl;
	}
	std::string getPrefix(User *user)
	{
		return ":" + user->getNickname() + "!" + user->getUsername() + "@" + user->getHostname();
	}
	std::string getTime()
	{
		time_t rawtime;
		struct tm *timeinfo;
		char buffer[80];

		std::time(&rawtime);
		timeinfo = localtime(&rawtime);

		strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timeinfo);
		return std::string(buffer);
	}
	std::string getColor(int fd)
	{
		std::string colors[] = {RED, YELLOW, BLUE, MAGENTA, CYAN, WHITE, BLACK};
		std::string color = colors[fd % 7];
		return color;
	}
}