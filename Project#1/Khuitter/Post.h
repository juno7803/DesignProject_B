#pragma once
#include <string>
#include "Subject.h"
#include "AcsPrivate.h"
#include "AcsPublic.h"
#include <iostream>
using namespace std;

class Post // 자식
	: public Subject // 부모
	// 자식은 부모를 사용할 수 있지만, 부모는 자식것을 사용할 수 없다.
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