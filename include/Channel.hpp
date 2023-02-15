#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "User.hpp"
#include "Server.hpp"
#include <iostream>
#include <vector>

class User;
class Server;

class Channel
{
	private:
		std::vector<User *> users;
		std::vector<User *> operators;
		User *owner;
		std::string name;
	public:
		Channel();
		Channel(std::string name);
		~Channel();
		void addUser(User *user);
		void removeUser(User *user);
		void addOperator(User *user);
		void removeOperator(User *user);
		void setOwner(User *user);
		void setName(std::string name);
		std::string getName();
		std::vector<User *> getUsers();
		std::vector<User *> getOperators();
		User *getOwner();
		User *getUser(User *user);
		User *getUser(std::string nickname);
		User *getOperator(User *user);
		void cedeOwnership(Server *server);
};

#endif