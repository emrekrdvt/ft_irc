#ifndef AUTH_HPP
# define AUTH_HPP

#include "Execute.hpp"
#include "utils.hpp"

class Execute;

namespace auth
{
	void authPassword(User *user, Server *server, std::string password);
	void handleAuth(User *user, Execute exec, std::string message, Server *server);
	bool checkAuth(User *user, Server *server, std::string command);
}

#endif