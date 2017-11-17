#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <ostream>
#include "User.h"
using namespace std;

class App
{
public:
	App();
	~App();

	void run();
	// 내가 추가한 함수들
	void StartMenu();
	void swap(int a, int b);
private:
	void readFiles();
	void writeFiles();

	User* findUserById(int id);

	void save_relation(); 
	void save_user();
	void save_post();
	void save_message();
	void save_timeline();

	void load_relation(); 
	void load_user(); 
	void load_post(); 
	void load_message(); 
	void load_timeline(); 

	void InitialMenu();

	void login();
	void logout();
	
	void PostTab();
	void writePost();
	void printMyPosting();
	void printTimeline();

	void MessageTab();
	void sendMessage();
	void printMessages();

	void FriendTab();
	void friendRecommendation();
	void friendType1();
	void friednType2();
	void requestFriend();

	void acceptFriend();
	void rejectFriend();


	int GetCommand(int maxCommand);

	vector<User*> userList;

	// 내가 추가한 변수들
	User* loginedUser;
	int postnum = 1;
	int messagenum = 1;
	int flag = 0; // 세이브할때 내가만든 플래그(endl 오류 잡기위함)
};

// 참고사항
// 타임라인엔 친구가 된 이후에 올라온 글만 추가!
// 즉 이전의 글은 업데이트해서 넣어줄 필요가 없다.

// 추가 기능

// < 메시지 >
// 읽음 표시 - 변수 추가
// 전달

// < 포스트 >
// 좋아요 표시

// 공유 기능
// 공유 : 타임라인의 글을 MyPost로 복사하는 것임! ( 원랜 내 탐라지만 여기서의 탐라 의미는 친구들글 올라오는것! )
