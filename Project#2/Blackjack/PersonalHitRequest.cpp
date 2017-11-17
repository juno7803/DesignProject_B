#include "PersonalHitRequest.h"

PersonalHitRequest::PersonalHitRequest()
{
	command_name = "���� : �߰� ī�� ����";
}


PersonalHitRequest::~PersonalHitRequest()
{
}

void PersonalHitRequest::setdb(vector<User*>* playerdb, vector<Card*>* carddb, priority_queue<UserScoreInfo, vector<UserScoreInfo>, less<UserScoreInfo>>* scorePQdb,bool* passornot,int idx)
{
	playerList = playerdb;
	cardDeck = carddb;
	scorePQ = scorePQdb;
	this->passornot = passornot;
	requestedPlayerIndex = idx;
}

void PersonalHitRequest::setplayerindex(int index)
{
	requestedPlayerIndex = index;
}

void PersonalHitRequest::execute()
{
	playerList->at(requestedPlayerIndex)->getcards()->push_back(*(cardDeck->begin()));
	cardDeck->erase(cardDeck->begin());
	cout << "��";
	playerList->at(requestedPlayerIndex)->printMyInformation();
	cout << "\n����������������������������������" << endl;
	cout << "��"<<playerList->at(requestedPlayerIndex)->getname() << "���� ī�带 �޾ҽ��ϴ�" << endl;
	cout << "����������������������������������" << endl;
}