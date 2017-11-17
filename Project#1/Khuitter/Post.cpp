#include "Post.h"



Post::Post()
{
}


Post::~Post()
{
}

void Post::setUserID(int ud)
{
	userId = ud;
}

void Post::setItemID(int id)
{
	itemId = id;
}

void Post::setContent(string ct)
{
	content = ct;
}

void Post::setAcs(Accessibility * acs)
{
	this->acs = acs;
}

int Post::getud()
{
	return userId;
}

int Post::getitid()
{
	return itemId;
}

string Post::getct()
{
	return content;
}

void Post::setContentByKB()
{
	string ct;
	cout << "내용을 입력하세요 : ";
	cin >> ct;
	content = ct;
}

Accessibility * Post::getAcs()
{
	return acs;
}
