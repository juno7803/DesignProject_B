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
	bool operator<(const UserScoreInfo& b)const; // �켱���� ť ũ������� �����ǰ� �ʿ��ϴ�.
	// < : true
private:
	User* user;
	int score; // ī�� ���� ��
};