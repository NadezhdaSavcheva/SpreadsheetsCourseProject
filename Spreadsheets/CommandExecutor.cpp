#include "CommandExecutor.h"

CommandExecutor::~CommandExecutor() {
	delete command;
}

void CommandExecutor::setCommand(Command* command) {
    this->command = command;
}

void CommandExecutor::executeCommand(Table& table, unsigned short commandNumber) {
    if (command) {
        command->execute(table, commandNumber);
    }
}