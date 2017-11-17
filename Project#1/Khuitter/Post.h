#pragma once
#include <string>
#include "Subject.h"
#include "AcsPrivate.h"
#include "AcsPublic.h"
#include <iostream>
using namespace std;

class Post // �ڽ�
	: public Subject // �θ�
	// �ڽ��� �θ� ����� �� ������, �θ�� �ڽİ��� ����� �� ����.
{
public:
	Post();
	~Post();

	void setUserID(int ud);
	void setItemID(int id);
	void setContent(string ct);
	void setAcs(Accessibility* acs);

	int getud();
	int getitid();
	string getct();

	void setContentByKB();

	Accessibility* getAcs();

private:
	int userId;
	int itemId;
	string content;
	Accessibility* acs;
};