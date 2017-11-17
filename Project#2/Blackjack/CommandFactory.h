#include "CheckLoser.h"
#include "CheckWinner.h"
#include "InitialCardDistribution.h"
#include "PersonalHitRequest.h"
#include "Replay.h"
#pragma once
class CommandFactory
{
private:
	CommandFactory();

public:
	~CommandFactory(); // ����ڰ� ������ �� ������ privateȭ ��

	Command* getCommand(int id);
	static CommandFactory* getInstace();
private:
	static CommandFactory* instance;
};