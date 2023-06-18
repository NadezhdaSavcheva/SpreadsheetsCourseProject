#pragma once
#include "Command.h"

class CommandFactory {
	CommandFactory() = default;
	CommandFactory(const CommandFactory&) = delete;
	CommandFactory& operator=(const CommandFactory&) = delete;
public:
	Command* getCommand(unsigned short commandNumber) const;
	static CommandFactory& getInstance();
};

