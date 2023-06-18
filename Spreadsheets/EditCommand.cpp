#include "EditCommand.h"

void EditCommand::execute(Table& table, unsigned short commandNumber) {
	size_t row = 0;
	size_t column = 0;
	MyString newValue;
	std::cout << "Enter the row number of the cell: ";
	std::cin >> row;
	std::cout << "Enter the column number of the cell: ";
	std::cin >> column;
	std::cout << "Enter the new value of the cell (Formulas must start with \"=\". If it is neither a number nor a formula, it must be in \"\"): ";
	std::cin >> newValue;

	try {
		table.editCell(row, column, newValue);
	}
	catch (std::exception exc) {
		std::cout << "The cell was not successfully edited. Check if the new value was written correctly and try again." << std::endl;
		return;
	}
}