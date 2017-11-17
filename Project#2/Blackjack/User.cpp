#include "User.h"



User::User()
{
	remainScore = 0;
}


User::~User()
{
}

void User::setid(int id)
{
	this->ID = id;
}

void User::setpw(string pw)
{
	this->pw = pw;
}

void User::setusername(string username)
{
	this->username = username;
}

void User::setremainscore(int remainscore)
{
	this->remainScore = remainscore;
}

int User::getid()
{
	return ID;
}

string User::getpw()
{
	return pw;
}

string User::getname()
{
	return username;
}

int User::getremainScore()
{
	return remainScore;
}

vector<Card*>* User::getcards()
{
	return &cardsInHand;
}

void User::Handwash()
{
	cardsInHand.clear();
}

void User::printMyInformation()
{
	cout << username << "´Ô ÀÇ Ä«µå: ";
	for (int i = 0; i < cardsInHand.size(); i++)
	{
		cardsInHand[i]->printMyInformation();
		cout << " ";
	}
}
