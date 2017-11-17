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
	// User* 형 벡터에 새로운 friends 추가
	void addRecievedFR(User* request);
	// 받은 친구요청 벡터

	void EraseRecieved(int command);
	
	void addPostToMyPosts(Post* newpost);
	// 내가쓴글에 저장

	void addTimeline(Post* newtime);

	void addToSendedMessage(Message* newmessage);
	void addToRecievedMessage(Message* newmessage);


	bool _writePost();
	// 공개포스트인지 비공개 포스트인지 선택하는 함수

	void update(int userId, int itemId, string content);
	// 내가 글을 썼을때, 공개 포스트이면 친구들의 timeline에 추가한다.

	int GetCommand(int maxCommand);

private:
	vector<Post*> myPosts; // 내가 쓴글
	vector<Post*> timeline; // 친구들이 쓴 글(그 중 공개한 글)
	vector<Message*> sentMessage;
	vector<Message*> recievedMessage;
	vector<User*> friendList;
	vector<User*> recievedFriendRequest;

	int id;
	string pw;
	map<string, string> attrs;
};