#ifndef ERROR_HPP
# define ERROR_HPP

#define USAGEERROR 1
#define PORTERROR 2
#define PORTNUMBERERROR 3
#define SOCKETERROR 4
#define BINDERROR 5
#define LISTENERROR 6
#define FCNTLERROR 7
#define SETSOCKOPTERROR 8 
#define POLLERROR 9
#define ACCEPTERROR 10
#define RECVERROR 11
#define GETHOSTNAMEERROR 12

#include <iostream>
#include <sys/socket.h>
#include "Server.hpp"
#include "User.hpp"

namespace error
{
	void error(std::string msg, int exitCode);
	void checkSocket(int sock, std::string function, int exitCode);
	void checkArgs(int argc, char *argv[]);
	void checkRecv(int fd, char *buffer, int size);
}

#endif