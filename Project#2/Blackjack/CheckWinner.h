#pragma once
#include "Command.h"
#include <queue>
using namespace std;
class CheckWinner :
	public Command
{
public:
	CheckWinner();
	~CheckWinner();

	void setdb(vector<User*>* playerdb, priority_queue<UserScoreInfo, vector<UserScoreInfo>, less<UserScoreInfo>>* scorePQdb,int bat,int startnum);
	void execute();
private:
	vector<User*>* playerList;
	priority_queue<UserScoreInfo, vector<UserScoreInfo>, less<UserScoreInfo>>* scorePQ;
	int batscore;
	int startnum;
};