#include <iostream>
#include "CommandExecutor.h"
#include "CommandFactory.h"

int main()
{
	std::cout << "Welcome!" << std::endl << std::endl;

	CommandExecutor *executor = new CommandExecutor();
	Table table;

	while (true) {
		std::cout << "Menu:" << std::endl;
		std::cout << "1. Open" << std::endl;
		std::cout << "2. Print" << std::endl;
		std::cout << "3. Edit" << std::endl;
		std::cout << "4. Save" << std::endl;
		std::cout << "5. Close" << std::endl;
		std::cout << "6. Exit" << std::endl << std::endl;

		unsigned short option;
		std::cout << "Choose an option from the menu: ";
		std::cin >> option;
		std::cout << std::endl;

		executor->setCommand(CommandFactory::getInstance().getCommand(option));
		executor->executeCommand(table, option);

		if (option == 6)
			return 0;

		std::cout << std::endl;
	}

	delete executor;
	return 0;
}
