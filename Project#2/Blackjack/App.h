#include "CommandFactory.h"
#include "GameCommandInvoker.h"
#include <fstream>
#include <vector>
#include <ctime>
#pragma once
class App
{
public:
	App();
	~App();

	int GetCommand(int maxCommand);

	void run();
	// �� ����
	void login();
	// �α���
	void readUserFile();
	void saveUserFile();
	// ���� �ε�
	void playGame();
	void deckInitialize();
	void deckshuffle();
	int setbattingscore();

	void checkLoser();
	void checkWinner();
	void initialDistribution();
	void personalHitRequest();
	// ���� ����
	void showReplay();
	// ���÷���

	void players();

private:
	vector<User*> userList; 
	// ���Ϸε忡 ������ ������ ��� ��

	vector<User*> playerList;
	// �α��ο� ������ ������ ��� ��
	vector<User*> playerListForReplay; // App::login() ���� �ʱ�ȭ

	vector<Card*> deck;
	vector<Card*> shuffledDeckForReplay; // App::playGame() ���� �ʱ�ȭ

	priority_queue<UserScoreInfo, vector<UserScoreInfo>, less<UserScoreInfo>> scorePQ;
	priority_queue<UserScoreInfo, vector<UserScoreInfo>, less<UserScoreInfo>> scorePQForReplay;

	GameCommandInvoker gci;

	// �߰�
	CommandFactory* cf;
	int batscore = 0;
	int startplayernum = playerList.size();
	Replay* replay;
	int logflag;

	bool passornot = true;

	int playerindex = 0;
	int replayflag = 0;
};