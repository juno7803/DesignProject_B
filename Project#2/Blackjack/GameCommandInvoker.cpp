#include "GameCommandInvoker.h"



GameCommandInvoker::GameCommandInvoker()
{
}


GameCommandInvoker::~GameCommandInvoker()
{
}

void GameCommandInvoker::setcommand(Command * ncommand)
{
	curCommand = ncommand;
}

void GameCommandInvoker::executeCommand()
{
	curCommand->execute();
}
