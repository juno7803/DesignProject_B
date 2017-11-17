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
	score = 0; // 실험해보고 아님 빼자
	vector<Card*> temp;
	vector<Card*> Ace; // Ace가 여러개 일수 있음

	for (int i = 0; i < user->getcards()->size(); i++)
	{
		int cardnum = user->getcards()->at(i)->getnumber();
		if (cardnum == 14)
		{
			Ace.push_back(user->getcards()->at(i));
			continue;
			// A는 A벡터에 몰아넣음
		}
		// A를 제외한 나머지 임시벡터에 몰아넣음
		temp.push_back(user->getcards()->at(i));

	}

	// A를 제외하고 스코어 계산 (A가 없다면 계산 완료)
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

	// 따로 보관했던 Ace가 있다면
	if (Ace.size() != 0)
	{
		// A 세개있고 스코어 8이라고 치자!
		for (int i = 0; i < Ace.size(); i++)
		{
			// 첫번째 A
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
	cout << user->getname() << "님: " << this->score << "점 ";
}

// 유저가 카드를 받는다
// 카드를 size 만큼 갖고 있을 것
// 21 - 11 = 10 
// 10 보다 작거나 같으면 11을 
// 10 보다 크면 1을 고른다

// 여러개를 뽑는다

bool UserScoreInfo::operator<(const UserScoreInfo & b)const
{
	if (this->score < b.score) return true;
	else return false;
}