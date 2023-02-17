#include "error.hpp"

namespace error
{
	void error(std::string msg, int exitCode)
	{
		std::cerr << "Error: " << msg << std::endl;
		std::cerr << "Exiting with code " << exitCode << std::endl;
		exit(exitCode);
	}
	void checkSocket(int sock, std::string function, int exitCode)
	{
		if (sock == -1)
			error(function + "() didn't work as excepted", exitCode);
	}
	void checkRecv(int fd, char *buffer, int size)
	{
		if (recv(fd, buffer, size, 0) < 0) {
			if (errno != EWOULDBLOCK)
				error("recv() didn't work as excepted", RECVERROR);
		}
		return ;

	}
	void checkArgs(int argc, char *argv[])
	{
		std::string usage = "Usage: " + std::string(argv[0]) + " <port> <password>";
		if (argc != 3)
			error(usage , USAGEERROR);
		try {
			int port = std::stoi(argv[1]);
			if (port < 1024 || port > 65535)
				error("Port must be between 1024 and 65535", PORTERROR);
		} catch (std::exception &e) {
			error("Port must be a number", PORTNUMBERERROR);
		}
	}
}
