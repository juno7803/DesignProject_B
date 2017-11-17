#pragma once
#include <string>
using namespace std;
class Observer
{
public:
	Observer();
	~Observer();

	virtual void update(int userId, int itemId, string content) = 0;
	// User에서 정의한다.
};