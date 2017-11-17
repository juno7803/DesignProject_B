#include "Replay.h"



Replay::Replay()
{
	command_name = "�������������÷��� �������������";
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
		cout << "����������������������������������" << endl;
		cout << "��   1.��������        2.����   ��" << endl;
		cout << "����������������������������������" << endl;
		cout << "��";
		int num;
		cin >> num;
		cout << "����������������������������������" << endl;
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
