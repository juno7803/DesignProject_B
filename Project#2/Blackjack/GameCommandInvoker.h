#pragma once
#include "Command.h"
class GameCommandInvoker
{
public:
	GameCommandInvoker();
	~GameCommandInvoker();

	void setcommand(Command* ncommand);
	// setcommand에서 실행할 커맨드를 curCommand에 저장하고 실행까지 시킨다
	void executeCommand();
private:
	Command* curCommand;
};