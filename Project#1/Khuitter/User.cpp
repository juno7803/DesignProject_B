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
	// ���ɾ� ��!!!!!!!!
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
	cout << "����Ʈ�� �������� �Ͻðڽ��ϱ�? " << endl;
	cout << "1. ��" << endl;
	cout << "2. �ƴϿ�" << endl;
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
	Post* newPost = new Post; // �ϳ� �ӽ÷� ����
	newPost->setUserID(userId);
	newPost->setItemID(itemId);
	newPost->setContent(content);
	// �Ķ���ͷ� ���� ���� ������ ���ο� ����Ʈ
	timeline.push_back(newPost); // ����Ʈ�� Ÿ�Ӷ��ο� ����
}

int User::GetCommand(int maxCommand)
{
	while (true)
	{
		int command;
		cout << "��ȣ�� �Է��ϼ��� : ";
		cin >> command;

		if (cin.fail())
		{
			cout << "�ùٸ��� ���� �Է��Դϴ�." << endl;
			cin.clear();
			cin.ignore(256, '\n'); // cin�� ��������ִ� �ڵ� 
		}
		else
		{
			if (command <= maxCommand && command >= 0)
			{
				return command;
			}
			else
			{
				cout << "�ùٸ��� ���� �Է��Դϴ�." << endl;
			}
		}
	}
	cout << "������������������������������������������������������������������" << endl;
}