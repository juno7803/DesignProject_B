#include "InitialCardDistribution.h"



InitialCardDistribution::InitialCardDistribution()
{
	command_name = "┏턴 : 카드 분배";
}

InitialCardDistribution::InitialCardDistribution(vector<User*>* playerdb, vector<Card*>* carddb)
{
	playerList = playerdb;
	cardDeck = carddb;
}

InitialCardDistribution::~InitialCardDistribution()
{
}

void InitialCardDistribution::execute()
{
	for (int i = 0; i < playerList->size(); i++)
	{
		playerList->at(i)->setremainscore((playerList->at(i)->getremainScore()) - batscore);
	}
	cout << command_name << endl;
	for (int i = 0; i < playerList->size(); i++)
	{
		int cnt = 0;
		while (cnt < 2)
		{
			(playerList->at(i))->getcards()->push_back(*(cardDeck->begin()));
			cardDeck->erase(cardDeck->begin());
			cnt += 1;
			// 2장 나눠주기 완료
		}
		cout << "▷" << playerList->at(i)->getname() << "님의 카드 : ";
		for (int k = 0; k < playerList->at(i)->getcards()->size(); k++)
		{
			playerList->at(i)->getcards()->at(k)->printMyInformation();
			cout << "  ";
		}
		cout << endl;
	}
	cout << "┗카드분배를 완료하였습니다" << endl;
	cout << "─────────────────" << endl;
}

void InitialCardDistribution::setdb(vector<User*>* playerdb, vector<Card*>* carddb,int batscore)
{
	playerList = playerdb;
	cardDeck = carddb;
	this->batscore = batscore;
}
