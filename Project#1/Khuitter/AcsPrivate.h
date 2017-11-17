#pragma once
#include "Accessibility.h"
class AcsPrivate :
	public Accessibility
{
public:
	AcsPrivate();
	~AcsPrivate();

	void update(vector<Observer*> oblist, int userid, int itemid, string content);
};

