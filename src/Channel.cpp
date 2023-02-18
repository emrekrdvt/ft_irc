#include "Channel.hpp"

Channel::Channel(){}

Channel::Channel(std::string name)
{
	this->name = name;
	this->topic = "";
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
	if (this->users.size() == 1)
	{
		this->owner = NULL;
		return ;
	}
	srand(time(NULL));
	std::vector<User *> temp = this->users;
	std::vector<User *>::iterator it = temp.begin();
	std::vector<User *>::iterator ite =temp.end();
	temp.erase(std::remove(temp.begin(), temp.end(), this->owner), temp.end());
	int random = rand() % temp.size();
	this->owner = temp[random];
	this->addOperator(this->owner);
	it = temp.begin();
	while (it != ite)
	{
		int toSend = (*it)->getFd();
		server->sender(toSend, utils::getPrefix(*it) + " MODE " + this->name + " +o " + (this->owner)->getNickname());
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

void Channel::setTopic(std::string topic)
{
	this->topic = topic;
}

std::string Channel::getTopic()
{
	return (this->topic);
}