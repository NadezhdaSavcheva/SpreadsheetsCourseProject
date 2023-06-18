#pragma once
#include "Command.h"
#include "Table.h"

class CloseCommand : public Command {
public:
	void execute(Table& table, unsigned short commandNumber) override;
};

