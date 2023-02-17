#include "bot.hpp"

bool is_it_number(std::string number)
{
    std::string::const_iterator it = number.begin();
    while (it != number.end() && std::isdigit(*it))
        ++it;
    return (!number.empty() && it == number.end());
}

bool check_args(int ac, char **av)
{
	if (ac != 4)
	{
        std::cout << "argument error" << std::endl;
        return false;
    }
	if (!is_it_number(av[2]))
	{
        std::cout << "port must be number" << std::endl;
        return false;
    }
	return true;
}

int main(int ac, char **av)
{
	if (!check_args(ac, av))
		return -1;
	bot bot(std::string(av[1]),std::atoi(av[2]),std::string(av[3]));
	bot.run_bot();
	return 0;
}
