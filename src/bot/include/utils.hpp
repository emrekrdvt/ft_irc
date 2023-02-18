#ifndef UTILS_HPP
# define UTILS_HPP

#include <iostream>
#include <vector>
#include <fstream>

std::vector<std::string> str_parse(std::string str, std::string delim);
std::string trim(std::string buffer);
std::vector<std::string> read_file(std::string filename);

#endif