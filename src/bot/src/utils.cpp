#include "utils.hpp"

std::string trim(std::string buffer)
{
	std::string trimmed = buffer;
	trimmed.erase(trimmed.find_last_not_of("\r\n") + 1);
	return trimmed;
}

std::vector<std::string> str_parse(std::string str, std::string delim)
{
	std::vector<std::string> parts;
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