#include "CheckLoser.h"



CheckLoser::CheckLoser()
{
	command_name = "┏턴 : 탈락자 확인";
}


CheckLoser::~CheckLoser()
{
}

void CheckLoser::setdb(vector<User*>* playerdb, priority_queue<UserScoreInfo, vector<UserScoreInfo>, less<UserScoreInfo>>* scorePQdb,int batscore)
{
	playerList = playerdb;
	scorePQ = scorePQdb;
	this->batscore = batscore;
}

void CheckLoser::execute()
{
	int cnt = 0;
	cout << command_name << endl;
	for (int i = 0; i < playerList->size(); i++)
	{
		UserScoreInfo temp(playerList->at(i));
		temp.calculateScore();
		if (temp.getscore() > 21)
		{
			temp.setscore(0); // 점수를 0으로 세팅하고
			scorePQ->push(temp); // 우선순위 큐에 저장하며(등수)
			cout << "┗"<<playerList->at(i)->getname() << "님은 탈락하셨습니다" << endl;
			playerList->at(i)->Handwash();
			playerList->erase(playerList->begin() + i); // 플레이어 목록에서 제외한다
			cnt += 1;
		}
	}
	if (cnt == 0)
	{
		cout << "┗탈락자가 없습니다" << endl;
	}
	cout << "─────────────────" << endl;
	system("pause");
	system("cls");
} 