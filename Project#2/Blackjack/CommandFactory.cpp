#include "CommandFactory.h"

CommandFactory* CommandFactory::instance = nullptr;

	
CommandFactory::CommandFactory()
{
}


CommandFactory::~CommandFactory()
{
}

Command * CommandFactory::getCommand(int id)
{
	Command* newCommand;
	switch (id)
	{
	case 1:
		newCommand = new InitialCardDistribution();
		return newCommand;
	case 2:
		newCommand = new PersonalHitRequest();
		return newCommand;
	case 3:
		newCommand = new CheckLoser();
		return newCommand;
	case 4:
		newCommand = new CheckWinner();
		return newCommand;
	}
}

CommandFactory * CommandFactory::getInstace()
{
	if (instance == nullptr)
	{
		CommandFactory* newCommandFact = new CommandFactory();
		instance = newCommandFact;
		return instance;
	}
	else
	{
		return instance;
	}
}