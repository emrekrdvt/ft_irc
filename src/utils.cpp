#include "utils.hpp"

namespace utils
{
	std::string trimBuffer(std::string buffer)
	{
		std::string trimmed = buffer;
		trimmed.erase(trimmed.find_last_not_of("\n\r") + 1);
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
	void printClient(std::string msg, int fd)
	{
		std::cout << "[Client " << fd << "] " << msg << std::endl;
	}
	std::string getProtocol(User *user)
	{
		return ":" + user->getNickname() + "!" + user->getUsername() + "@" + "localhost ";
	}
}