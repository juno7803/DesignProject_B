#pragma once
#include "Observer.h"
#include <vector>
using namespace std;
//Subject -> 뉴스,정보 < 여기선 Post에 해당!
class Subject
{
public:
	Subject();
	~Subject();
	void setOblist(vector<Observer*>& friendList);

private:
	vector<Observer*> oblist;
	// void setOblist(vector<Observer*>& friendList); 위치가 여기가 맞음?
};

