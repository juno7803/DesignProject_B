#pragma once
#include "Command.h"
#include <queue>
using namespace std;
class CheckLoser :
	public Command
{
public:
	CheckLoser();
	~CheckLoser();

	void setdb(vector<User*>* playerdb, priority_queue<UserScoreInfo, vector<UserScoreInfo>, less<UserScoreInfo>>* scorePQdb,int batscore);
	void execute();
private:
	vector<User*>* playerList;
	priority_queue<UserScoreInfo, vector<UserScoreInfo>, less<UserScoreInfo>>* scorePQ;
	// 제일 큰게 맨위에 있음 -> 작은것부터 깊이 넣는다.
	int batscore;
};