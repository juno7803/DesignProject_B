#pragma once
#include "Observer.h"
#include <vector>
using namespace std;
//Subject -> ����,���� < ���⼱ Post�� �ش�!
class Subject
{
public:
	Subject();
	~Subject();
	void setOblist(vector<Observer*>& friendList);

private:
	vector<Observer*> oblist;
	// void setOblist(vector<Observer*>& friendList); ��ġ�� ���Ⱑ ����?
};

