#include "CheckLoser.h"



CheckLoser::CheckLoser()
{
	command_name = "���� : Ż���� Ȯ��";
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
			temp.setscore(0); // ������ 0���� �����ϰ�
			scorePQ->push(temp); // �켱���� ť�� �����ϸ�(���)
			cout << "��"<<playerList->at(i)->getname() << "���� Ż���ϼ̽��ϴ�" << endl;
			playerList->at(i)->Handwash();
			playerList->erase(playerList->begin() + i); // �÷��̾� ��Ͽ��� �����Ѵ�
			cnt += 1;
		}
	}
	if (cnt == 0)
	{
		cout << "��Ż���ڰ� �����ϴ�" << endl;
	}
	cout << "����������������������������������" << endl;
	system("pause");
	system("cls");
} 