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
	// ���� �߰��� �Լ���
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

	// ���� �߰��� ������
	User* loginedUser;
	int postnum = 1;
	int messagenum = 1;
	int flag = 0; // ���̺��Ҷ� �������� �÷���(endl ���� �������)
};

// �������
// Ÿ�Ӷ��ο� ģ���� �� ���Ŀ� �ö�� �۸� �߰�!
// �� ������ ���� ������Ʈ�ؼ� �־��� �ʿ䰡 ����.

// �߰� ���

// < �޽��� >
// ���� ǥ�� - ���� �߰�
// ����

// < ����Ʈ >
// ���ƿ� ǥ��

// ���� ���
// ���� : Ÿ�Ӷ����� ���� MyPost�� �����ϴ� ����! ( ���� �� Ž������ ���⼭�� Ž�� �ǹ̴� ģ����� �ö���°�! )
