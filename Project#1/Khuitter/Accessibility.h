#pragma once
#include "Observer.h"
#include <vector>
using namespace std;

class Accessibility
// �߻� Ŭ����
{
public:
	Accessibility();
	~Accessibility();

	virtual void update(vector<Observer*> oblist, int userid, int itemid, string content) = 0;
};