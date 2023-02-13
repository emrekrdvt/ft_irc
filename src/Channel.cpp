#include "Channel.hpp"

Channel::Channel(){}

Channel::Channel(std::string name)
{
	this->name = name;
}

Channel::~Channel(){}

void Channel::addUser(User *user)
{
	this->users.push_back(user);
}

void Channel::removeUser(User *user)
{
	std::vector<User *>::iterator it = this->users.begin();
	std::vector<User *>::iterator ite = this->users.end();
	while (it != ite)
	{
		if (*it == user)
		{
			this->users.erase(it);
			break;
		}
		it++;
	}
}

void Channel::addOperator(User *user)
{
	this->operators.push_back(user);
}

void Channel::removeOperator(User *user)
{
	std::vector<User *>::iterator it = this->operators.begin();
	std::vector<User *>::iterator ite = this->operators.end();
	while (it != ite)
	{
		if (*it == user)
		{
			this->operators.erase(it);
			break;
		}
		it++;
	}
}

void Channel::setOwner(User *user)
{
	this->owner = user;
}

void Channel::setName(std::string name)
{
	this->name = name;
}

std::string Channel::getName()
{
	return (this->name);
}

std::vector<User *> Channel::getUsers()
{
	return (this->users);
}

std::vector<User *> Channel::getOperators()
{
	return (this->operators);
}

User *Channel::getOwner()
{
	return (this->owner);
}

User *Channel::getUser(User *user)
{
	std::vector<User *>::iterator it = this->users.begin();
	std::vector<User *>::iterator ite = this->users.end();
	while (it != ite)
	{
		if (*it == user)
			return (*it);
		it++;
	}
	return (NULL);
}

User *Channel::getOperator(User *user)
{
	std::vector<User *>::iterator it = this->operators.begin();
	std::vector<User *>::iterator ite = this->operators.end();
	while (it != ite)
	{
		if (*it == user)
			return (*it);
		it++;
	}
	return (NULL);
}
