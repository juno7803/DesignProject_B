#include "Message.h"



Message::Message()
{
}


Message::~Message()
{
}

int Message::getUserID()
{
	return userId;
}

int Message::getItemID()
{
	return itemId;
}

string Message::getContent()
{
	return content;
}

void Message::setUserID(int ud)
{
	userId = ud;
}

void Message::setItemID(int id)
{
	itemId = id;
}

void Message::setContent(string ct)
{
	content = ct;
}

void Message::setContentByKB()
{
	string ct;
	cout << "메시지의 내용을 입력하세요 :";
	cin >> ct;
	content = ct;
}
