#include "User.h"
#pragma once
class UserScoreInfo
{
public:
	UserScoreInfo(User* user);
	UserScoreInfo();
	~UserScoreInfo();

	int getscore();
	void setscore(int score);
	User* getuser();

	void calculateScore();
	void printMyInformation();
	bool operator<(const UserScoreInfo& b)const; // 우선순위 큐 크기비교위해 재정의가 필요하다.
	// < : true
private:
	User* user;
	int score; // 카드 숫자 합
};