#include "PrintCommand.h"

void PrintCommand::execute(Table& table, unsigned short commandNumber) {
	table.printTable();
}