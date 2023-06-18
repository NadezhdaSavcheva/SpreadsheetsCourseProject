#include "CloseCommand.h"

void CloseCommand::execute(Table& table, unsigned short commandNumber) {
	if (table.getChangesFlag() == true) {
		char answer[7];
		std::cout << "Do you want to save the changes to this file? (Enter \"yes\"/\"no\"/\"cancel\")" << std::endl;
		std::cin >> answer;

		if (strcmp(answer, "yes") == 0) {
			table.saveToFile(table.getFileName().c_str());
		}	
		else if (strcmp(answer, "no") == 0) {
			table.loadFromFile(table.getFileName().c_str());
			table.saveToFile(table.getFileName().c_str());
		}
		else if (strcmp(answer, "cancel") == 0) {
			return;
		}

	}
	
	std::cout << "File clossed successfully." << std::endl;
}