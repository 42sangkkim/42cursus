#include <string>
#include <iostream>
#include "Harl.hpp"

int	main(void)
{
	Harl		my_harl;
	std::string	input;

	std::cout << "Let's talk to Harl!" << std::endl;
	while (true)
	{
		std::cout << "[Me]" << std::endl << "> ";
		std::getline(std::cin, input);
		if (input.compare("EXIT") == 0)
			break ;
		else
		{
			std::cout << "[Harl]" << std::endl;
			my_harl.complain(input);
		}
	}
	return (0);
}