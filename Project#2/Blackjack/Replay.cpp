#include "Replay.h"



Replay::Replay()
{
	command_name = "────▶리플레이 재생◀────";
}


Replay::~Replay()
{
}

void Replay::clearReplay()
{
	replayLog.clear();
}

void Replay::addCommandToLog(Command * newCommand)
{
	replayLog.push_back(newCommand);
}

void Replay::execute()
{
	cout << command_name << endl;
	for (int i = 0; i < replayLog.size(); i++)
	{
		cout << "┌───────────────┐" << endl;
		cout << "│   1.다음으로        2.종료   │" << endl;
		cout << "└───────────────┘" << endl;
		cout << "▷";
		int num;
		cin >> num;
		cout << "─────────────────" << endl;
		switch (num)
		{
		case 1:
			replayLog[i]->execute();
			break;
		case 2:
			return;
		}
	}
}
