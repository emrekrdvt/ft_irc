#include "Server.hpp"
#include "check.hpp"

int main(int argc, char *argv[])
{
	error::checkArgs(argc, argv);
	Server server(std::stoi(argv[1]), argv[2]);
	system("clear");
	server.run();
	return (0);
}