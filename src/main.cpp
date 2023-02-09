#include "Server.hpp"
#include "check.hpp"

int main(int argc, char *argv[])
{
	check::checkArgs(argc, argv);
	Server server(std::stoi(argv[1]), argv[2]);
	server.run();
	return (0);
}