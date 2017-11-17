#include "Card.h"
#include "string"
#include <vector>
using namespace std;
#pragma once
class User
{
public:
	User();
	~User();

	void setid(int id);
	void setpw(string pw);
	void setusername(string username);
	void setremainscore(int remainscore);

	int getid();
	string getpw();
	string getname();
	int getremainScore();
	vector<Card*>* getcards();

	void Handwash();
	void printMyInformation();

private:
	int ID;
	string pw;
	string username;
	int remainScore;
	vector<Card*> cardsInHand;
};