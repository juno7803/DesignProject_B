#pragma once
#include "Accessibility.h"
class AcsPublic :
	public Accessibility
{
public:
	AcsPublic();
	~AcsPublic();

	void update(vector<Observer*> oblist, int userid, int itemid, string content);
};

