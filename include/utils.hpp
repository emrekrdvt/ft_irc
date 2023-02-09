#ifndef UTILS_HPP
# define UTILS_HPP

#include <iostream>
#include <vector>

namespace utils
{
	std::string trimBuffer(std::string buffer);
	std::vector<std::string> split(std::string str, std::string delim);
	void printClient(std::string msg, int fd);
}

#endif