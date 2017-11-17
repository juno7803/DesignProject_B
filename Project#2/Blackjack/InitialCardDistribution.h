#pragma once
#include "Command.h"
class InitialCardDistribution :
	public Command
{
public:
	InitialCardDistribution();
	InitialCardDistribution(vector<User*>*playerdb, vector<Card*>*carddb);
	~InitialCardDistribution();

	void execute();
	void setdb(vector<User*>*playerdb, vector<Card*>*carddb,int batscore);
private:
	vector<User*>* playerList;
	vector<Card*>* cardDeck; 
	int batscore;
};