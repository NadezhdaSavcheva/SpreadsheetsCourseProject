#pragma once
#include "Command.h"
#include "Table.h"

class PrintCommand : public Command {
public:
	void execute(Table& table, unsigned short commandNumber) override;
};

