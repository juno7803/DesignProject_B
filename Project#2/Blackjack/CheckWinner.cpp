#include "CheckWinner.h"



CheckWinner::CheckWinner()
{
}


CheckWinner::~CheckWinner()
{
}

void CheckWinner::setdb(vector<User*>* playerdb, priority_queue<UserScoreInfo, vector<UserScoreInfo>, less<UserScoreInfo>>* scorePQdb, int bat, int startnum)
{
	playerList = playerdb;
	scorePQ = scorePQdb;
	this->batscore = bat;
	this->startnum = startnum;
}

void CheckWinner::execute()
{
	int reward = 0, LargestScore = 0, Qsize = 0, count = 0;
	UserScoreInfo temp;
	vector<UserScoreInfo> players;

	for (int i = 0; i < playerList->size(); i++)
	{
		UserScoreInfo temp(playerList->at(i));
		temp.calculateScore();

		scorePQ->push(temp);
	}

	temp = scorePQ->top();
	LargestScore = temp.getscore();
	Qsize = scorePQ->size();

	while (!scorePQ->empty())
	{
		temp = scorePQ->top();
		if (temp.getscore() == LargestScore)
		{
			count += 1;
		}
		players.push_back(temp);
		scorePQ->pop();
	}
	reward = (Qsize*batscore) / count;

	cout << "����������������������������������" << endl;
	cout << "           ���� ����ǥ" << endl;
	cout << "----------------------------------" << endl;

	for (int i = 0; i < count; i++)
	{
		players[i].getuser()->setremainscore((players[i].getuser()->getremainScore()) + reward);
		players[i].printMyInformation();
		cout << "���� ��� ����: " << players[i].getuser()->getremainScore() << "��(���)" << endl;
	}
	for (int i = count; i < Qsize; i++)
	{
		players[i].printMyInformation();
		cout << "���� ��� ����: " << players[i].getuser()->getremainScore() << "��";
		if (players[i].getscore() == 0)
		{
			cout << "(Ż��)";
		}
		cout << endl;
	}
	
	// ���� ���� ������ ���� �ڵ�(����)
	for (int i = 0; i < playerList->size(); i++)
	{
		playerList->at(i)->Handwash(); // ���б� �ڵ�
	}

	playerList->clear(); // �α׾ƿ� �ڵ�

	cout << "����������������������������������" << endl;
	system("pause");
	system("cls");
}