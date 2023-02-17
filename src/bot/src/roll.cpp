#include "roll.hpp"

static std::string roll(int sides, int times)
{
	std::string result = "[ ";
	int total = 0;
	
	for (int i = 0; i < times; i++)
	{
		int roll = (rand() % sides) + 1;
		total += roll;
		result += std::to_string(roll) + " ";
	}
	result += "] = " + std::to_string(total);
	return result;
}

std::string rollCommand(std::string message)
{
	std::string result = "";
	std::string sides = "";
	std::string times = "";
	int i = 0;
	while (message[i] != 'd' && message[i] != '\0')
	{
		times += message[i];
		i++;
	}
	if (message[i] == '\0')
		return "Invalid roll command format\nExample: !roll 2d6";
	i++;
	while (message[i] != '\0')
	{
		sides += message[i];
		i++;
	}
	std::cout << "sides: " << sides << std::endl;
	std::cout << "times: " << times << std::endl;
	result = roll(std::stoi(sides), std::stoi(times));
	return result;
}