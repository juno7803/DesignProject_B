#include "Subject.h"



Subject::Subject()
{
}


Subject::~Subject()
{
}

void Subject::setOblist(vector<Observer*>& friendList)
{
	oblist = friendList;
}
