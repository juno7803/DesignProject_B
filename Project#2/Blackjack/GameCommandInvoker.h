#pragma once
#include "Command.h"
class GameCommandInvoker
{
public:
	GameCommandInvoker();
	~GameCommandInvoker();

	void setcommand(Command* ncommand);
	// setcommand���� ������ Ŀ�ǵ带 curCommand�� �����ϰ� ������� ��Ų��
	void executeCommand();
private:
	Command* curCommand;
};