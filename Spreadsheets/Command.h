#pragma once
#include "Table.h"

class Command {
public:
	virtual ~Command() = default;
	void virtual execute(Table& table, unsigned short commandNumber) = 0;
};