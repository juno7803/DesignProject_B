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
		cout << "����������������������������������" << endl;
		cout << "��                              ��" << endl;
		cout << "��     ��   Black Jack   ��     ��" << endl;
		cout << "��                              ��" << endl;
		cout << "����������������������������������" << endl;
		cout << "����������������������������������" << endl;
		cout << "1.���� ����" << endl;
		cout << "2.���÷��� ����" << endl;
		cout << "0.���α׷� ����" << endl;
		cout << "����������������������������������" << endl;
		cout << "��";
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
			cout << "�ٽ� �Է��� �ֽʽÿ�" << endl;
			return;
		}
	}
}

void App::players()
{
	logflag = 0;
	cout << "���÷����� �ο����� �Է��ϼ���" << endl;
	int playernum = GetCommand(userList.size());
	cout << "����������������������������������" << endl;
	while (logflag < playernum)
	{
		login();
	}
	for (int i = 0; i < playerList.size(); i++)
	{
		cout << playerList[i]->getname() << " �� ���� ����: " << playerList[i]->getremainScore() << " ��" << endl;
	}
	cout << "����������������������������������" << endl;
	system("pause");
	system("cls");
	playGame();
}


void App::login()
{
	int playernum = 0; // �÷��̾� ��(�α����� �÷��̾� ��)
	int id;
	string pw;

	cout << "�����̵� �Է��ϼ��� : ";
	cin >> id;
	cout << "����й�ȣ�� �Է��ϼ��� : ";
	cin >> pw;
	for (int i = 0; i < userList.size(); i++)
	{
		if (id == userList[i]->getid())
		{
			if (pw == userList[i]->getpw())
			{
				cout << "��" << userList[i]->getname() << "�� ȯ���մϴ�!" << endl;
				cout << "����������������������������������" << endl;
				playerList.push_back(userList[i]);
				logflag += 1;
				return;
			}
			else
			{
				cout << "��й�ȣ�� ��ġ���� �ʽ��ϴ�" << endl;
				return;
			}
		}
	}
	cout << "��ġ�ϴ� ���̵� �����ϴ�" << endl;
	return;
}
// ī�带 �޴� ����-> �α��� �� ����

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
	int hnum = 0; // �� ������ num
	int passcnt = 0;
	// ���÷��̴� �� ���Ӵ� �ѹ��� ��� ����
	replayflag = 0;
	replay->clearReplay();
	// ���÷��̿� playerlist
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
	// �� �ʱ�ȭ&����
	deckInitialize();
	deckshuffle();
	// ���÷��̿� deck
	for (int k = 0; k < deck.size(); k++)
	{
		shuffledDeckForReplay.push_back(NULL);
	}
	for (int k = 0; k < deck.size(); k++)
	{
		shuffledDeckForReplay[k] = new Card;
		*shuffledDeckForReplay[k] = *deck[k];
	}

	// ���� ����
	cout << "���������������� �����մϴ٢���������" << endl;
	batscore = setbattingscore();

	// Ŀ�ǵ� : �ʱ�й�
	initialDistribution();
	// Ŀ�ǵ� : Ż���� Ȯ��
	checkLoser();

	while (1)
	{
		if (passcnt == playerList.size())
		{
			break;
		}
		// �� Ż���ϰ� �Ѹ� ������ ���
		else if (playerList.size() == 1)
		{
			break;
		}
		passcnt = 0;
		// �������ʴ� : �ۿ� ǥ�� -> ������ ���� �̾ҵ� �� ���
		for (int i = 0; i < playerList.size(); i++) 
		{
			cout << "����" << playerList[i]->getname() << "���� �Ϣ�" << endl;
			cout << "��";
			playerList[i]->printMyInformation();
			cout << "\n����������������������������������" << endl;
			cout << "�� ī�带 ���� �� �����ðڽ��ϱ�?" << endl;
			cout << "��1. ��" << endl;
			cout << "��2. �ƴϿ�" << endl;
			cout << "��";
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
				cout << "����������������������������������" << endl;
				checkLoser();
				break;
			}
		}
		// �ƴϿ��� �÷��̾� ����ŭ ������ Ż���ϵ���!

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
			shuffledDeckForReplay.push_back(newCard); // ���÷��̿� ��
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
	cout << "��� ���� ����(���� ���� ����): ";
	cin >> score;
	cout << "      �� ��� ���� " << score <<"�� ��"<< endl;
	cout << "����������������������������������" << endl;
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
		cout << "�ظ��÷��̴� �� ���Ӵ� �ѹ��� ����� ��û �����մϴ�" << endl;
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
		cout << "�� : ";
		cin >> command;

		if (cin.fail())
		{
			cout << "���ùٸ��� ���� �Է��Դϴ�" << endl;
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
				cout << "���ùٸ��� ���� �Է��Դϴ�" << endl;
			}
		}
	}
	cout << "����������������������������������" << endl;
}
