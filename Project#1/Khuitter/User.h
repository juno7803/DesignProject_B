#pragma once
#include "Observer.h"
#include "Post.h"
#include "Message.h"
#include <vector>
#include <map>
using namespace std;

class User :
	public Observer
{
public:
	User();
	~User();

	int getId()
	{
		return id;
	}
	string getPw()
	{
		return pw;
	} 
	map<string,string> getattrs()
	{
		return attrs;
	}

	void setId(int id)
	{
		this->id = id;
	}
	void setPw(string pw)
	{
		this->pw = pw;
	}

	vector<User*> getFlist();
	vector<Post*> getMyPost();
	vector<Post*> getTimeline();
	vector<User*> getrecievedFR();
	vector<Message*> getsentmessage();
	vector<Message*> getrecievedmessage();

	void setAttrToKeyValueMap(string st, string atr);

	void addFriend(User* friends);
	// User* �� ���Ϳ� ���ο� friends �߰�
	void addRecievedFR(User* request);
	// ���� ģ����û ����

	void EraseRecieved(int command);
	
	void addPostToMyPosts(Post* newpost);
	// �������ۿ� ����

	void addTimeline(Post* newtime);

	void addToSendedMessage(Message* newmessage);
	void addToRecievedMessage(Message* newmessage);


	bool _writePost();
	// ��������Ʈ���� ����� ����Ʈ���� �����ϴ� �Լ�

	void update(int userId, int itemId, string content);
	// ���� ���� ������, ���� ����Ʈ�̸� ģ������ timeline�� �߰��Ѵ�.

	int GetCommand(int maxCommand);

private:
	vector<Post*> myPosts; // ���� ����
	vector<Post*> timeline; // ģ������ �� ��(�� �� ������ ��)
	vector<Message*> sentMessage;
	vector<Message*> recievedMessage;
	vector<User*> friendList;
	vector<User*> recievedFriendRequest;

	int id;
	string pw;
	map<string, string> attrs;
};