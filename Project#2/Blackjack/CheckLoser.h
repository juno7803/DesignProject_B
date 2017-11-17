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
	// ���� ū�� ������ ���� -> �����ͺ��� ���� �ִ´�.
	int batscore;
};