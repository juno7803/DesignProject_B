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
	// 앱 실행
	void login();
	// 로그인
	void readUserFile();
	void saveUserFile();
	// 파일 로드
	void playGame();
	void deckInitialize();
	void deckshuffle();
	int setbattingscore();

	void checkLoser();
	void checkWinner();
	void initialDistribution();
	void personalHitRequest();
	// 게임 실행
	void showReplay();
	// 리플레이

	void players();

private:
	vector<User*> userList; 
	// 파일로드에 성공한 유저들 담는 곳

	vector<User*> playerList;
	// 로그인에 성공한 유저들 담는 곳
	vector<User*> playerListForReplay; // App::login() 에서 초기화

	vector<Card*> deck;
	vector<Card*> shuffledDeckForReplay; // App::playGame() 에서 초기화

	priority_queue<UserScoreInfo, vector<UserScoreInfo>, less<UserScoreInfo>> scorePQ;
	priority_queue<UserScoreInfo, vector<UserScoreInfo>, less<UserScoreInfo>> scorePQForReplay;

	GameCommandInvoker gci;

	// 추가
	CommandFactory* cf;
	int batscore = 0;
	int startplayernum = playerList.size();
	Replay* replay;
	int logflag;

	bool passornot = true;

	int playerindex = 0;
	int replayflag = 0;
};