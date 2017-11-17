#include "AcsPublic.h"



AcsPublic::AcsPublic()
{
}


AcsPublic::~AcsPublic()
{
}

void AcsPublic::update(vector<Observer*> oblist, int userid, int itemid, string content)
{
	for (int i = 0; i < oblist.size(); i++)
	{
		oblist.at(i)->update(userid,itemid,content);
		// 모든 옵저버에 대하여 update 수행!
		// 여기서 옵저버는 친구들이라 할 수 있나?? - 질문
	}
}
