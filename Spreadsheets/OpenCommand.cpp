#include "OpenCommand.h"
#include <iostream>

void OpenCommand::execute(Table& table, unsigned short commandNumber) {
	char fileName[1024];
	std::cout << "Enter the file name of the spreadsheet you want to open: ";
	std::cin >> fileName;

	try {
		table.loadFromFile(fileName);
	}
	catch (std::exception exc) {
		std::cout << "Could not open the spreadsheet. Check is a file with the name " << fileName << " exists." << std::endl;
		return;
	}
	
	std::cout << "The spreadsheet is opened sucessfully." << std::endl;
}