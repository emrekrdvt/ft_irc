#include "bot.hpp"

bool bot::send_message_to_channel(std::string channel, std::string message)
{
    return (send_message("PRIVMSG " + channel + " :" + message));
}

bool bot::command_handler(std::string nick, std::string command, std::string message)
{
	command = trim(command);
	if (command == ":!help")
		return this->send_message_to_channel(nick, "I can help you on !roll !hello !ht !randvid commands");
    if (command == ":!hello")
        return this->send_message_to_channel(nick, "Hello, how are you!");
	if (command == ":!ht")
	{
		srand(time(NULL));
		std::string result = (rand() % 2 == 0) ? "HEAD" : "TAIL";
		return this->send_message_to_channel(nick, result);
	}

	if (command == ":!roll")	
	{
		std::cout << "message: " << message << std::endl;
		try
		{
			message = message.substr(message.find('!') + 1);
			message = message.substr(message.find('!') + 1);
			message = message.substr(message.find(' ') + 1);
			message = trim(message);
			std::string rollResult = rollCommand(message);
			return this->send_message_to_channel(nick, rollResult);
		}
		catch (std::exception &e)
		{
			return this->send_message_to_channel(nick, "Invalid roll command format\nExample: !roll 2d6");
		}
	}
	if (command == ":!randvid")
	{
		srand(time(NULL));
		std::vector<std::string> lines = read_file("./src/bot/videos.txt");
		if (lines.size() == 0)
			return this->send_message_to_channel(nick, "Error: Could not get random video");
		std::string result = lines[rand() % lines.size()];
		return this->send_message_to_channel(nick, result);
	}
	return false;
}

void bot::processData(std::string data)
{
    std::vector<std::string> lines = str_parse(data, "\n");
    for (size_t i = 0; i < lines.size(); i++)
    {
        if (lines[i].length() == 0)
            continue;
        std::vector<std::string> parts = str_parse(lines[i], " ");
        std::cout << lines[i] << std::endl;
        if (std::strstr(lines[i].c_str(), "PRIVMSG") != NULL)
        {
			std::string nick = parts[0].substr(1, parts[0].find('!') - 1);
			std::string command = parts[3];
            if (!command_handler(nick, command, lines[i]))
            {
                std::cout << "Invalid command" << std::endl;
                return ;
            }
        }
    }
}

bot::bot(std::string host, int port, std::string password)
{
	this->_host = host;
	this->_port = port;
	this->_password = password;
	this->_mynick = "bot";
    std::memset((char*) &_address, 0, sizeof(_address));
	_address.sin_family			=	AF_INET;
	_address.sin_port			=	htons(_port);
	_address.sin_addr.s_addr	=	inet_addr(_host.c_str());
    char hostname_c[1024];
	gethostname(hostname_c, 1024);
	this->_hostname = hostname_c;
}

void bot::run_bot(void)
{
    this->_serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if( this->_serverfd == -1)
	{
		std::cerr << "Socket error" << std::endl;
        close(this->_serverfd);
		return ;
	}
    int opt = 1;
    if(setsockopt(this->_serverfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) == -1 )
	{
		std::cerr << "Socket can't set" << std::endl;
		close(this->_serverfd);
		return ;
	}
	if (connect(_serverfd, (struct sockaddr *) &_address, sizeof(_address)) == -1)
	{
		std::cout << "Could not connect" << std::endl;
        close(this->_serverfd);
		return ;
	}
	if (send_message("PASS :" + _password) == false)
        return ;
	if (send_message("NICK " + _mynick) == false)
        return ;
	if (send_message("USER " + _mynick + " 0 " + this->getHostname() + " : " + _mynick) == false)
		return ;
    char buffer[1024];
    this->_connected = true;
    while (_connected)
    {
		std::memset(buffer, 0, 1024);
        int bytesReceived = recv(_serverfd, buffer, sizeof(buffer), 0);
        if (bytesReceived == 0)
        { 
            std::cout << "Disconnected from server." << std::endl;
            _connected = false;
        }
        else
        {
            buffer[bytesReceived] = '\0';
            processData(buffer);
        }
    }
    close(_serverfd);
}

bool bot::send_message(std::string message)
{
	message.append("\r\n");
	if (send(_serverfd,message.c_str(),message.size(),0) == -1)
	{
		std::cout << "Send error" << std::endl;
        close(this->_serverfd);
		return false;
	}
	return (true);
}

std::string bot::getHostname()
{
    return this->_hostname;
}

bot::~bot(){}