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

void Channel::cedeOwnership(Server *server)
{
	if (this->users.size() == 2 && this->getUser("bot") != NULL)
	{
		this->owner = NULL;
		return ;
	}
	if (this->users.size() == 1)
	{
		this->owner = NULL;
		return ;
	}
	srand(time(NULL));
	std::vector<User *>::iterator it = this->users.begin();
	std::vector<User *>::iterator ite = this->users.end();
	for (int i = 0; i < rand() % static_cast<int>(this->users.size()); i++)
	{
		if (it == ite)
			it = this->users.begin();
		it++;
	}
	this->owner = *it;
	this->addOperator(*it);
	it = this->users.begin();
	while (it != ite)
	{
		int toSend = (*it)->getFd();
		server->sender(toSend, utils::getPrefix(*it) + " MODE " + this->name + " +o " + (*it)->getNickname());
		it++;
	}
}

User *Channel::getUser(std::string nickname)
{
	std::vector<User *>::iterator it = this->users.begin();
	std::vector<User *>::iterator ite = this->users.end();
	while (it != ite)
	{
		if ((*it)->getNickname() == nickname)
			return (*it);
		it++;
	}
	return (NULL);
}