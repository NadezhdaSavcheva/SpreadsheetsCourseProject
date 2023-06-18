#include "CommandFactory.h"
#include "OpenCommand.h"
#include "CloseCommand.h"
#include "SaveCommand.h"
#include "ExitCommand.h"
#include "PrintCommand.h"
#include "EditCommand.h"

Command* CommandFactory::getCommand(unsigned short commandNumber) const {
	switch (commandNumber) {
	case 1:
		return new OpenCommand();
	case 2:
		return new PrintCommand();
	case 3:
		return new EditCommand();
	case 4:
		return new SaveCommand();
	case 5:
		return new CloseCommand();
	case 6:
		return new ExitCommand();
	}
}

CommandFactory& CommandFactory::getInstance() {
	static CommandFactory factory;
	return factory;
}