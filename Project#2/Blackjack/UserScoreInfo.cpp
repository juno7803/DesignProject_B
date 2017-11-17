#include "UserScoreInfo.h"



UserScoreInfo::UserScoreInfo(User * user)
{
	this->user = user;
	this->score = 0;
}

UserScoreInfo::UserScoreInfo()
{
	score = 0;
}


UserScoreInfo::~UserScoreInfo()
{
}

int UserScoreInfo::getscore()
{
	return score;
}

void UserScoreInfo::setscore(int score)
{
	this->score = score;
}

User * UserScoreInfo::getuser()
{
	return user;
}

void UserScoreInfo::calculateScore()
{
	score = 0; // �����غ��� �ƴ� ����
	vector<Card*> temp;
	vector<Card*> Ace; // Ace�� ������ �ϼ� ����

	for (int i = 0; i < user->getcards()->size(); i++)
	{
		int cardnum = user->getcards()->at(i)->getnumber();
		if (cardnum == 14)
		{
			Ace.push_back(user->getcards()->at(i));
			continue;
			// A�� A���Ϳ� ���Ƴ���
		}
		// A�� ������ ������ �ӽú��Ϳ� ���Ƴ���
		temp.push_back(user->getcards()->at(i));

	}

	// A�� �����ϰ� ���ھ� ��� (A�� ���ٸ� ��� �Ϸ�)
	for (int j = 0; j < temp.size(); j++)
	{
		int tempnum = temp[j]->getnumber();
		if (tempnum == 11 || tempnum == 12 || tempnum == 13)
		{
			score += 10;
		}
		else
		{
			score += tempnum;
		}
	}

	// ���� �����ߴ� Ace�� �ִٸ�
	if (Ace.size() != 0)
	{
		// A �����ְ� ���ھ� 8�̶�� ġ��!
		for (int i = 0; i < Ace.size(); i++)
		{
			// ù��° A
			if (score <= 10)
			{
				score += 11;
			}
			// 
			else
			{
				score += 1;
			}
		}
	}
}

void UserScoreInfo::printMyInformation()
{
	cout << user->getname() << "��: " << this->score << "�� ";
}

// ������ ī�带 �޴´�
// ī�带 size ��ŭ ���� ���� ��
// 21 - 11 = 10 
// 10 ���� �۰ų� ������ 11�� 
// 10 ���� ũ�� 1�� ����

// �������� �̴´�

bool UserScoreInfo::operator<(const UserScoreInfo & b)const
{
	if (this->score < b.score) return true;
	else return false;
}