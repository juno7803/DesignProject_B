#include "Command.h"
#include <queue>
#pragma once
class PersonalHitRequest :
	public Command
{
public:
	PersonalHitRequest();
	~PersonalHitRequest();

	void setdb(vector<User*>* playerdb, vector<Card*>* carddb, priority_queue<UserScoreInfo, vector<UserScoreInfo>, less<UserScoreInfo>>* scorePQdb,bool* passornot,int idx);
	void setplayerindex(int index);
	void execute();
private:
	vector<User*>* playerList;
	vector<Card*>* cardDeck;
	priority_queue<UserScoreInfo, vector<UserScoreInfo>, less<UserScoreInfo>>* scorePQ;
	int requestedPlayerIndex;
	bool* passornot;
};