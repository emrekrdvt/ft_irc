#ifndef EXECUTE_HPP
#define EXECUTE_HPP

#include <iostream>
#include "numeric.hpp"
#include "Server.hpp"

class Server;

typedef std::pair<std::string, std::function<void(int &, Server *, std::string)> > Command;

class Execute{
    private:
        std::vector<Command> commands;
        static void join(int &fd, Server *server, std::string message);
		static void part(int &fd,Server *server, std::string message);
		static void privmsg(int &fd, Server *server, std::string message);
		static void quit(int &fd, Server *server, std::string message);
		static void nick(int &fd, Server *server, std::string message);
		static void ping(int &fd, Server *server, std::string message);
		static void kick(int &fd, Server *server, std::string message);
		static void pass(int &fd, Server *server, std::string message);
		static void user(int &fd, Server *server, std::string message);
		static void who(int &fd, Server *server, std::string message);
		static void notice(int &fd, Server *server, std::string message);
		static void mode(int &fd, Server *server, std::string message);
		static void cap(int &fd, Server *server, std::string message);
    public:
        Execute();
        ~Execute();
        void execute(int &fd, Server *server, std::string command);
        std::string getCmd(std::string command);
};

#endif