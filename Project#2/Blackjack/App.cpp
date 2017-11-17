#include "App.h"

App::App()
{
	replay = new Replay;
	readUserFile();
	cf->getInstace();
}


App::~App()
{
	saveUserFile();
}

void App::run()
{
	while (1)
	{

		int num = 0;
		cout << "┌───────────────┐" << endl;
		cout << "│                              │" << endl;
		cout << "│     ▶   Black Jack   ◀     │" << endl;
		cout << "│                              │" << endl;
		cout << "└───────────────┘" << endl;
		cout << "─────────────────" << endl;
		cout << "1.게임 실행" << endl;
		cout << "2.리플레이 실행" << endl;
		cout << "0.프로그램 종료" << endl;
		cout << "─────────────────" << endl;
		cout << "▶";
		cin >> num;
		switch (num)
		{
		case 1:
			players();
			break;
		case 2:
			showReplay();
			break;
		case 0:
			return;
		default:
			cout << "다시 입력해 주십시오" << endl;
			return;
		}
	}
}

void App::players()
{
	logflag = 0;
	cout << "┌플레이할 인원수를 입력하세요" << endl;
	int playernum = GetCommand(userList.size());
	cout << "─────────────────" << endl;
	while (logflag < playernum)
	{
		login();
	}
	for (int i = 0; i < playerList.size(); i++)
	{
		cout << playerList[i]->getname() << " 님 남은 점수: " << playerList[i]->getremainScore() << " 점" << endl;
	}
	cout << "─────────────────" << endl;
	system("pause");
	system("cls");
	playGame();
}


void App::login()
{
	int playernum = 0; // 플레이어 수(로그인할 플레이어 수)
	int id;
	string pw;

	cout << "┌아이디를 입력하세요 : ";
	cin >> id;
	cout << "└비밀번호를 입력하세요 : ";
	cin >> pw;
	for (int i = 0; i < userList.size(); i++)
	{
		if (id == userList[i]->getid())
		{
			if (pw == userList[i]->getpw())
			{
				cout << "▷" << userList[i]->getname() << "님 환영합니다!" << endl;
				cout << "─────────────────" << endl;
				playerList.push_back(userList[i]);
				logflag += 1;
				return;
			}
			else
			{
				cout << "비밀번호가 일치하지 않습니다" << endl;
				return;
			}
		}
	}
	cout << "일치하는 아이디가 없습니다" << endl;
	return;
}
// 카드를 받는 순서-> 로그인 한 순서

void App::readUserFile()
{
	ifstream ifs;
	ifs.open("User.txt");
	int userid, remainScore;
	string pw, username;


	while (!ifs.eof())
	{
		User* temp = new User;
		ifs >> userid >> pw >> username >> remainScore;
		temp->setid(userid);
		temp->setpw(pw);
		temp->setusername(username);
		temp->setremainscore(remainScore);
		userList.push_back(temp);
	}
	ifs.close();
}

void App::saveUserFile()
{
	ofstream ofs;
	ofs.open("User.txt");
	for (int i = 0; i < userList.size(); i++)
	{
		ofs << userList[i]->getid() << "\t";
		ofs << userList[i]->getpw() << "\t";
		ofs << userList[i]->getname() << "\t";
		ofs << userList[i]->getremainScore();
		if (i != userList.size() - 1)
		{
			ofs << endl;
		}
	}
	ofs.close();
}

void App::playGame()
{
	int hnum = 0; // 힛 질문용 num
	int passcnt = 0;
	// 리플레이는 한 게임당 한번만 출력 가능
	replayflag = 0;
	replay->clearReplay();
	// 리플레이용 playerlist
	for (int j = 0; j < playerList.size(); j++)
	{
		playerListForReplay.push_back(NULL);
	}
	for (int j = 0; j < playerList.size(); j++)
	{
		playerListForReplay[j] = new User;
		*playerListForReplay[j] = *playerList[j];
	}
	//int num = 0;
	// 덱 초기화&셔플
	deckInitialize();
	deckshuffle();
	// 리플레이용 deck
	for (int k = 0; k < deck.size(); k++)
	{
		shuffledDeckForReplay.push_back(NULL);
	}
	for (int k = 0; k < deck.size(); k++)
	{
		shuffledDeckForReplay[k] = new Card;
		*shuffledDeckForReplay[k] = *deck[k];
	}

	// 게임 시작
	cout << "────▶게임을 시작합니다◀────" << endl;
	batscore = setbattingscore();

	// 커맨드 : 초기분배
	initialDistribution();
	// 커맨드 : 탈락자 확인
	checkLoser();

	while (1)
	{
		if (passcnt == playerList.size())
		{
			break;
		}
		// 다 탈락하고 한명만 남았을 경우
		else if (playerList.size() == 1)
		{
			break;
		}
		passcnt = 0;
		// 누구차례다 : 앱에 표시 -> 힛에선 누가 뽑았따 만 얘기
		for (int i = 0; i < playerList.size(); i++) 
		{
			cout << "│▷" << playerList[i]->getname() << "님의 턴◁" << endl;
			cout << "│";
			playerList[i]->printMyInformation();
			cout << "\n─────────────────" << endl;
			cout << "┌ 카드를 한장 더 받으시겠습니까?" << endl;
			cout << "│1. 예" << endl;
			cout << "│2. 아니오" << endl;
			cout << "▶";
			cin >> hnum;
			switch (hnum)
			{
			case 1:
				playerindex = i;
				personalHitRequest();
				checkLoser();
				break;
			case 2:
				passcnt += 1;
				cout << "─────────────────" << endl;
				checkLoser();
				break;
			}
		}
		// 아니오를 플레이어 수만큼 누르면 탈출하도록!

	}
	checkWinner();
}


void App::deckInitialize()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 2; j < 15; j++)
		{
			Card* newCard = new Card;
			newCard->setsuit(i);
			newCard->setnumber(j);
			deck.push_back(newCard);
			shuffledDeckForReplay.push_back(newCard); // 리플레이용 덱
		}
	}
}

void App::deckshuffle()
{
	int n = 0;
	srand(time(0));

	while (n < 100)
	{
		for (int i = 0; i < (52 - 1); i++)
		{
			int r = i + (rand() % (52 - i));
			Card* temp = deck[i]; deck[i] = deck[r]; deck[r] = temp;
		}
		n++;
	}
}

int App::setbattingscore()
{
	int score;
	cout << "배당 점수 설정(남은 점수 이하): ";
	cin >> score;
	cout << "      ◎ 배당 점수 " << score <<"점 ◎"<< endl;
	cout << "─────────────────" << endl;
	return score;
}

void App::checkLoser()
{
	CheckLoser* command = (CheckLoser*)cf->getCommand(3);
	command->setdb(&playerList, &scorePQ,batscore);
	gci.setcommand(command);
	gci.executeCommand();

	CheckLoser* command1 = (CheckLoser*)cf->getCommand(3);
	command1->setdb(&playerListForReplay, &scorePQForReplay,batscore);
	replay->addCommandToLog(command1);
}

void App::checkWinner()
{
	CheckWinner* command = (CheckWinner*)cf->getCommand(4);
	command->setdb(&playerList, &scorePQ, batscore, startplayernum);
	gci.setcommand(command);
	gci.executeCommand();

	CheckWinner* command1 = (CheckWinner*)cf->getCommand(4);
	command1->setdb(&playerListForReplay, &scorePQForReplay, batscore, startplayernum);
	replay->addCommandToLog(command1);

}

void App::initialDistribution()
{
	//InitialCardDistribution* command = (InitialCardDistribution*)cf->getCommand(1);
	InitialCardDistribution* command;
	command = dynamic_cast<InitialCardDistribution*>(cf->getCommand(1));
	command->setdb(&playerList, &deck,batscore);
	gci.setcommand(command);
	gci.executeCommand();

	InitialCardDistribution* command1 = (InitialCardDistribution*)cf->getCommand(1);
	command1->setdb(&playerListForReplay, &shuffledDeckForReplay,batscore);
	replay->addCommandToLog(command1);
}

void App::personalHitRequest()
{
	PersonalHitRequest* command = (PersonalHitRequest*)cf->getCommand(2);
	command->setdb(&playerList, &deck, &scorePQ, &passornot, playerindex);
	gci.setcommand(command);
	gci.executeCommand();

	PersonalHitRequest* command1 = (PersonalHitRequest*)cf->getCommand(2);
	command1->setdb(&playerListForReplay, &shuffledDeckForReplay, &scorePQForReplay, &passornot, playerindex);
	replay->addCommandToLog(command1);
}

void App::showReplay()
{
	if (replayflag >= 1)
	{
		cout << "※리플레이는 한 게임당 한번만 무료로 시청 가능합니다" << endl;
		system("pause");
		system("cls");
		return;
	}
	replay->execute();
	replayflag += 1;
}

int App::GetCommand(int maxCommand)
{
	while (true)
	{
		int command;
		cout << "▶ : ";
		cin >> command;

		if (cin.fail())
		{
			cout << "│올바르지 않은 입력입니다" << endl;
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
				cout << "│올바르지 않은 입력입니다" << endl;
			}
		}
	}
	cout << "─────────────────" << endl;
}
