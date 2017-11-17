#pragma once
#include "Command.h"
class Replay :
	public Command
{
public:
	Replay();
	~Replay();

	void clearReplay();

	void addCommandToLog(Command* newCommand);
	void execute();
private:
	vector<Command*> replayLog;
};

