#include "SaveCommand.h"

void SaveCommand::execute(Table& table, unsigned short commandNumber) {
	try {
		table.saveToFile(table.getFileName().c_str());
	}
	catch (std::exception exc) {
		std::cout << "The file was not saved successfully. Try again later." << std::endl;
		return;
	}

	std::cout << "File saved successfully." << std::endl;
}