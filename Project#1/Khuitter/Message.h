#pragma once
#include <string>
#include <iostream>
using namespace std;
class Message
{
public:
	Message();
	~Message();

	int getUserID();
	int getItemID();
	string getContent();

	void setUserID(int ud);
	void setItemID(int id);
	void setContent(string ct);

	void setContentByKB();

private:
	int userId;
	int itemId;
	string content;
};

