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
		// ��� �������� ���Ͽ� update ����!
		// ���⼭ �������� ģ�����̶� �� �� �ֳ�?? - ����
	}
}
