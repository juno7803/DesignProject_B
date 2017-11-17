#include "User.h"



User::User()
{
}


User::~User()
{
}

vector<User *> User::getFlist()
{
	return friendList;
}

vector<Post*> User::getMyPost()
{
	return myPosts;
}

vector<Post*> User::getTimeline()
{
	return timeline;
}

vector<User*> User::getrecievedFR()
{
	return recievedFriendRequest;
}

vector<Message*> User::getsentmessage()
{
	return sentMessage;
}

vector<Message*> User::getrecievedmessage()
{
	return recievedMessage;
}

void User::setAttrToKeyValueMap(string st, string atr)
{
	attrs.insert(pair<string, string>(st,atr));
	// 어케씀 맵!!!!!!!!
}

void User::addFriend(User * friends)
{
	friendList.push_back(friends);
}

void User::addRecievedFR(User * request)
{
	recievedFriendRequest.push_back(request);
}

void User::EraseRecieved(int command)
{
	recievedFriendRequest.erase(recievedFriendRequest.begin() + command);
}

void User::addPostToMyPosts(Post * newpost)
{
	myPosts.push_back(newpost);
}

void User::addTimeline(Post * newtime)
{
	timeline.push_back(newtime);
}

void User::addToSendedMessage(Message * newmessage)
{
	sentMessage.push_back(newmessage);
}

void User::addToRecievedMessage(Message * newmessage)
{
	recievedMessage.push_back(newmessage);
}

bool User::_writePost()
{
	int num;
	cout << "포스트를 공개설정 하시겠습니까? " << endl;
	cout << "1. 네" << endl;
	cout << "2. 아니요" << endl;
	num = GetCommand(2);
	if (num == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void User::update(int userId, int itemId, string content)
{
	Post* newPost = new Post; // 하나 임시로 선언
	newPost->setUserID(userId);
	newPost->setItemID(itemId);
	newPost->setContent(content);
	// 파라미터로 받은 값들 저장한 새로운 포스트
	timeline.push_back(newPost); // 포스트를 타임라인에 저장
}

int User::GetCommand(int maxCommand)
{
	while (true)
	{
		int command;
		cout << "번호를 입력하세요 : ";
		cin >> command;

		if (cin.fail())
		{
			cout << "올바르지 않은 입력입니다." << endl;
			cin.clear();
			cin.ignore(256, '\n'); // cin시 오류잡아주는 코드 
		}
		else
		{
			if (command <= maxCommand && command >= 0)
			{
				return command;
			}
			else
			{
				cout << "올바르지 않은 입력입니다." << endl;
			}
		}
	}
	cout << "▷───────────────────────────────◁" << endl;
}