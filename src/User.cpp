#include "User.hpp"

// Constructors and destructors
User::User(){}

User::~User(){}

User::User(int fd){
	this->fd = fd;
	this->auth = false;
	auths[0] = Auth("NICK", false);
	auths[1] = Auth("USER", false);
	auths[2] = Auth("PASS", false);
}

// Getters and setters

std::string User::getUsername()
{
	return (this->username);
}

std::string User::getNickname()
{
	return (this->nickname);
}

void User::setUsername(std::string username)
{
	this->username = username;
}

void User::setNickname(std::string nickname)
{
	this->nickname = nickname;
}

void User::setFd(int fd)
{
	this->fd = fd;
}

int User::getFd()
{
	return (this->fd);
}

bool User::getAuth()
{
	return (this->auth);
}

void User::setAuth(bool auth)
{
	this->auth = auth;
}

std::string User::getHostname()
{
	return (this->hostname);
}

void User::setHostname(std::string hostname)
{
	this->hostname = hostname;
}

void User::setMode(int mode)
{
	this->mode = mode;
}

int User::getMode()
{
	return (this->mode);
}

std::string User::getRealname()
{
	return (this->realname);
}

void User::setRealname(std::string realname)
{
	this->realname = realname;
}

void User::setAuths(std::string command, bool auth)
{
	for (int i = 0; i < 3; i++)
	{
		if (auths[i].first == command)
			auths[i].second = auth;
	}
}

bool User::checkAuths()
{
	for (int i = 0; i < 3; i++)
	{
		if (auths[i].second == false)
			return (false);
	}
	return (true);
}

Auth *User::getAuths()
{
	return (this->auths);
}