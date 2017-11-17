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

	cout << "─────────────────" << endl;
	cout << "           최종 순위표" << endl;
	cout << "----------------------------------" << endl;

	for (int i = 0; i < count; i++)
	{
		players[i].getuser()->setremainscore((players[i].getuser()->getremainScore()) + reward);
		players[i].printMyInformation();
		cout << "남은 배당 점수: " << players[i].getuser()->getremainScore() << "점(우승)" << endl;
	}
	for (int i = count; i < Qsize; i++)
	{
		players[i].printMyInformation();
		cout << "남은 배당 점수: " << players[i].getuser()->getremainScore() << "점";
		if (players[i].getscore() == 0)
		{
			cout << "(탈락)";
		}
		cout << endl;
	}
	
	// 다음 게임 실행을 위한 코드(리셋)
	for (int i = 0; i < playerList->size(); i++)
	{
		playerList->at(i)->Handwash(); // 손털기 코드
	}

	playerList->clear(); // 로그아웃 코드

	cout << "─────────────────" << endl;
	system("pause");
	system("cls");
}