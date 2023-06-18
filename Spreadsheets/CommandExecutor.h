#pragma once
#include "Command.h"
#include "Table.h"

class CommandExecutor {
private:
	Command* command;
public:
	CommandExecutor() = default;
	CommandExecutor(const CommandExecutor&) = delete;
	CommandExecutor& operator=(const CommandExecutor&) = delete;
	~CommandExecutor();

	void setCommand(Command* command);

	void executeCommand(Table& table, unsigned short commandNumber);
};

