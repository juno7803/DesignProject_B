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
	~CommandFactory(); // 사용자가 생성할 수 없도록 private화 함

	Command* getCommand(int id);
	static CommandFactory* getInstace();
private:
	static CommandFactory* instance;
};