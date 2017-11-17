#pragma once
#include "Observer.h"
#include <vector>
using namespace std;

class Accessibility
// 추상 클래스
{
public:
	Accessibility();
	~Accessibility();

	virtual void update(vector<Observer*> oblist, int userid, int itemid, string content) = 0;
};