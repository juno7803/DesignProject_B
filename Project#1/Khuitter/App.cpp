#include "App.h"



App::App()
{
	readFiles();
}


App::~App()
{
	writeFiles();
}

void App::run()
{
	cout << "����������������������������������������������������������������������" << endl;
	cout << "��                                                                  ��" << endl;
	cout << "��                       ��    ��huitter    ��                      ��" << endl;
	cout << "��                                                                  ��" << endl;
	cout << "����������������������������������������������������������������������" << endl;
	InitialMenu();
}

void App::StartMenu()
{
	while (1)
	{
		cout << "\n����� : " << loginedUser->getattrs()["�̸�"] << endl;
		cout << "�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�" << endl;
		cout << "1. ����Ʈ ��" << endl;
		// �� �߰�
		// �� �� ����
		// Ÿ�Ӷ��� ����

		cout << "2. �޽��� ��" << endl;
		// �޽��� ������
		// 1.���� �޽��� ����
		// 2.���� �޽��� ����
		// 3.ī��� ó�� ���̱�

		cout << "3. ģ�� ��" << endl;
		// 1. ģ�� ��õ�ޱ�
		// (1) ģ������ ģ���� ���� ���(�ణ �����ϰ� ����)
		// (2) �Ӽ��� �����̻� ���� ģ�� ���
		// *****(����) �˻���ɸ� ���� ���⼭ �ٷ� �߰�����
		// (����ó��)
		// (1) �̹� �߰��� ģ���� ����ϸ� �ȵ�

		// 2. ģ�� �߰��ϱ�
		// (����ó��)
		// 1. �̹� �߰��� ģ���� �߰� �Ұ�
		// 2. ���� ģ���� �ߺ����� �߰��Ǹ� �ȵȴ�.
		cout << "0. �ڷΰ���" << endl;

		int command = GetCommand(3);
		switch (command)
		{
		case 1:
			cout << endl;
			PostTab();
			break;
		case 2:
			cout << endl;
			MessageTab();
			break;
		case 3:
			cout << endl;
			FriendTab();
			break;
		case 0:
			return;
		}
	}
}

void App::swap(int a, int b)
{
}

void App::readFiles()
{
	load_user();
	load_relation();
	load_message();
	load_post();
	load_timeline();
}

void App::writeFiles()
{
	save_user();
	save_relation();
	save_message();
	save_post();
	save_timeline();
}

User * App::findUserById(int id)
{
	for (int i = 0; i < userList.size(); i++)
	{
		if (userList.at(i)->getId() == id)
		{
			return userList.at(i);
			// ���̵� ��ġ�ϴ� ������ �ּ� ����
		}
	}
	return nullptr;
}

void App::save_relation()
{
	ofstream ofs("friend.txt");
	ofstream ofs2("requested.txt");
	for (int i = 0; i < userList.size(); i++)
	{
		ofs << userList[i]->getId() << "\t"; // ���� ���̵�
		ofs << userList[i]->getFlist().size() << "\t"; // ģ�� ī��Ʈ
		for (int j = 0; j < userList[i]->getFlist().size(); j++)
		{
			ofs << userList[i]->getFlist()[j]->getId(); // ģ������ ���̵�
			if (j != userList[i]->getFlist().size()-1)
				ofs << "\t";
		}
		if (i != userList.size()-1)
		{
			ofs << endl;
		}
	}
	for (int i = 0; i < userList.size(); i++)
	{
		ofs2 << userList[i]->getId() << "\t";
		ofs2 << userList[i]->getrecievedFR().size() << "\t";
		for (int j = 0; j < userList[i]->getrecievedFR().size(); j++)
		{
			ofs2 << userList[i]->getrecievedFR()[j]->getId();
			if (j != userList[i]->getrecievedFR().size()-1)
				ofs2 << "\t";
		}
		if (i != userList.size()-1)
		{
			ofs2 << endl;
		}
	}
	ofs.close();
	ofs2.close();
}

void App::save_user()
{
	ofstream ofs("user.txt");
	for (int i = 0; i < userList.size(); i++)
	{
		ofs << userList[i]->getId() << "\t";
		ofs << userList[i]->getPw() << "\t";
		ofs << userList[i]->getattrs()["�̸�"] << "\t";
		ofs << userList[i]->getattrs()["����"] << "\t";
		ofs << userList[i]->getattrs()["����"] << "\t";
		ofs << userList[i]->getattrs()["�б�"] << "\t";
		ofs << userList[i]->getattrs()["����"];
		if (i != userList.size()-1)
		{
			ofs << endl;
		}
	}
	ofs.close();
}

void App::save_post()
{
	ofstream ofs("post.txt");
	flag = 0;
	for (int i = 0; i < userList.size(); i++)
	{
		if (userList[i]->getMyPost().size() == 0)
		{
			continue;
		}
		if (flag != 0)
		{
			ofs << endl;
		}
		flag += 1;
		for (int j = 0; j < userList[i]->getMyPost().size(); j++)
		{
			if (j != 0)
			{
				ofs << endl;
			}
			ofs << userList[i]->getId() << "\t";
			ofs << userList[i]->getMyPost()[j]->getitid() << "\t";
			ofs << userList[i]->getMyPost()[j]->getct();
		}
	}
	ofs.close();
}

void App::save_message()
{
	// �޴¾��̵�� ��� �ؾ����� ���
	// �ߺ��Ǵ� ����Ʈ ��� �������� ���
	ofstream ofs("message.txt");
	flag = 0;
	// �����޽����� �ø��� �ȴ�! < ���� : �� �����̹Ƿ�, ���� ����� ���̵�� ��������� ���̵� �ִ�.
	for (int i = 0; i < userList.size(); i++)
	{
		if (userList[i]->getrecievedmessage().size() == 0)
		{
			continue;
		}
		// ��Ƽ���� �ǳʶٴٰ� ���� �����޽����� �ִ� ����� ó���� �����ߴ�.
		// ó���� ������� ���ؾ���. �� ó���� ��� ǥ������?

		// ���� ��Ƽ���� �ȸ����� �Ѿ������ flag�� 0�̰� ���������� ��������� �ʿ��ϹǷ� �÷��׸� 1 ������Ų��.
		// flag ���� ������Ѵ�. �ֳĸ� ���������̱� ������ post���� �ٲ�� ���⵵ �ٲ�� �����Ƿ�!!
		// <�ذ�å>
		// flagp(post) , flagm(message), flagt(timeline) ���� �������
		if (flag != 0) 
		{
			ofs << endl; 
		}
		flag += 1;
		for (int j = 0; j < userList[i]->getrecievedmessage().size(); j++)
		{
			if (j != 0)
			{
				ofs << endl;
			}
			ofs << userList[i]->getrecievedmessage()[j]->getUserID() << "\t"; // ���� �������� (UserID)
			ofs << userList[i]->getId() << "\t"; // �������� �������� (toUserID)
			ofs << userList[i]->getrecievedmessage()[j]->getItemID() << "\t";
			ofs << userList[i]->getrecievedmessage()[j]->getContent();
		}
	}
	ofs.close();
}

void App::save_timeline()
{
	ofstream ofs("timeline.txt");
	flag = 0;
	for (int i = 0; i < userList.size(); i++)
	{
		if (userList[i]->getTimeline().size() == 0)
		{
			continue;
		}
		if (flag != 0) // �� �ڵ尡 Ʋ��
		{
			ofs << endl;
		}
		flag += 1;
		for (int j = 0; j < userList[i]->getTimeline().size(); j++)
		{
			if (j != 0)
			{
				ofs << endl;
			}
			ofs << userList[i]->getId() << "\t";
			ofs << userList[i]->getTimeline()[j]->getud() << "\t";
			ofs << userList[i]->getTimeline()[j]->getitid() << "\t";
			ofs << userList[i]->getTimeline()[j]->getct();
		}
	}
	ofs.close();
}


void App::load_relation()
{
	ifstream ifs1("friend.txt");
	ifstream ifs2("requested.txt");

	while (!ifs1.eof())// ������ ������ ����
	{
		int userId, friendsCount, friendId;
		ifs1 >> userId >> friendsCount;

		User* CurUser = findUserById(userId);

		for (int i = 0; i < friendsCount; i++)
		{
			ifs1 >> friendId;
			User* friends = findUserById(friendId);
			if (friends == nullptr)
			{
				return;
			}
			CurUser->addFriend(friends);
			// friendList ���Ϳ� ����(�߰�)
		}
	}

	while (!ifs2.eof())
	{
		int userId, requestedCount, requestId;
		ifs2 >> userId >> requestedCount;

		User* CurUser = findUserById(userId);

		for (int i = 0; i < requestedCount; i++)
		{
			ifs2 >> requestId;
			User* requested = findUserById(requestId);
			if (requested == nullptr)
			{
				return;
			}
			CurUser->addRecievedFR(requested);
			// reciecedFriendRequest�� ����(�߰�)
		}
	}

	ifs1.close();
	ifs2.close();
}

void App::load_user()
{
	ifstream ifs("user.txt");
	int userId;
	string pw, username, attr1, attr2, attr3, attr4;

	while (!ifs.eof())
	{
		ifs >> userId >> pw >> username >> attr1 >> attr2 >> attr3 >> attr4;
		User* CurUser = new User; // ������ �ӽ� ��ü

		CurUser->setId(userId);
		CurUser->setPw(pw);
		CurUser->setAttrToKeyValueMap("�̸�", username);
		CurUser->setAttrToKeyValueMap("����", attr1);
		CurUser->setAttrToKeyValueMap("����", attr2);
		CurUser->setAttrToKeyValueMap("�б�", attr3);
		CurUser->setAttrToKeyValueMap("����", attr4);

		userList.push_back(CurUser);
	}
	ifs.close();
}

void App::load_post()
{
	ifstream ifs("post.txt");
	int userid, itemid;
	string content;

	while (!ifs.eof())
	{
		ifs >> userid;
		Post* newPost = new Post;
		// �����Ҵ� �ϴ� ������? -> ���ϰ� Post������������ ����� NULL�̱� ������ �����Ҵ����� ��ü�� �ν��Ͻ�ȭ ������Ѵ�!
		newPost->setUserID(userid);
		ifs >> itemid;
		newPost->setItemID(itemid);
		ifs >> content;
		newPost->setContent(content);

		User* postedUser = findUserById(userid);
		if (postedUser == nullptr)
		{
			return;
		}
		postedUser->addPostToMyPosts(newPost);
	}
	ifs.close();
}

void App::load_message()
{
	ifstream ifs("message.txt");
	int userid, toid, itemid;
	string content;
	while (!ifs.eof())
	{
		ifs >> userid >> toid;
		Message* newMessage = new Message();
		newMessage->setUserID(userid);
		ifs >> itemid;
		newMessage->setItemID(itemid);
		ifs >> content;
		newMessage->setContent(content);

		User* sendedUser = findUserById(userid);
		if (sendedUser == nullptr)
		{
			return;
		}
		sendedUser->addToSendedMessage(newMessage);

		User* recievingUser = findUserById(toid);
		recievingUser->addToRecievedMessage(newMessage);
	}
	ifs.close();
}

void App::load_timeline()
{
	ifstream ifs("timeline.txt");
	int timelineid, userid, postid;
	string content;
	while (!ifs.eof())
	{
		Post* Timeline = new Post;
		ifs >> timelineid >> userid >> postid >> content;
		Timeline->setUserID(userid);
		Timeline->setItemID(postid);
		Timeline->setContent(content); // �׷� �� �ʿ��Ѱ� �ƴѵ�?
		for (int i = 0; i < userList.size(); i++)
		{
			if (userList.at(i)->getId() == timelineid)
			{
				userList.at(i)->addTimeline(Timeline);
			}
		}
	}
	ifs.close();
}

void App::InitialMenu()
{
	while (1)
	{
		cout << "Khuitter�� �������" << endl;
		cout << "1. �α��� " << endl;
		cout << "2. �α׾ƿ�" << endl;
		cout << "0. ����" << endl;
		// �α��� �����ϸ� StartMenu() �ҷ��´�.
		int command = GetCommand(2);
		switch (command)
		{
		case 1:
			login();
			break;
		case 2:
			logout();
			break;
		case 0:
			return;
		}
	}
}

void App::login()
{
	//loginedUser = �α����� �����ּ�;

	string name, pw;

	cout << "�̸� : ";
	cin >> name;
	cout << "��й�ȣ : ";
	cin >> pw;

	for (int i = 0; i < userList.size(); i++)
	{
		if ((userList.at(i)->getattrs()["�̸�"]) == name) // ���� �̸��� ã�Ҵ�!
		{
			if (userList.at(i)->getPw() == pw)
			{
				cout << "�α��ο� �����Ͽ����ϴ�!" << endl;
				loginedUser = userList.at(i);
				StartMenu(); // ��~��!
				return; // ���⼭ ���Ͼ��ϴϱ� ������ ����������..
			}
			else
			{
				cout << "��й�ȣ�� Ʋ�Ƚ��ϴ�!" << endl;
				return;
			}
		}
	}
	cout << "��ġ�ϴ� �̸��� ���� ����ڰ� �����ϴ�!" << endl;
	return;

}

void App::logout()
{
	loginedUser = NULL;
	cout << "���������� �α׾ƿ� �Ǿ����ϴ�!" << endl;
}

void App::PostTab()
{
	while (1)
	{
		cout << endl;
		cout << "�� ����Ʈ �� ��" << endl;
		cout << "1. ����Ʈ �߰�" << endl;
		cout << "2. ���� ����" << endl;
		cout << "3. Ÿ�Ӷ��� ����" << endl;
		cout << "0. �ڷ� ����" << endl;

		int command = GetCommand(3);
		switch (command)
		{
		case 1:
			cout << endl;
			writePost();
			break;
		case 2:
			cout << endl;
			printMyPosting();
			break;
		case 3:
			cout << endl;
			printTimeline();
			break;
		case 0:
			return;
		}
	}
}

void App::writePost()
{
	// ���� ���� ����!
	// case 1 ���� ����Ʈ�� ��������
	Post* newPost = new Post;
	Accessibility* acs = newPost->getAcs();
	vector<Observer*> newOb;

	newPost->setUserID(loginedUser->getId()); // ���̵� ����
	newPost->setContentByKB(); // ���� ����
	postnum += 1;
	newPost->setItemID(postnum); // ����Ʈ ���̵� ����, ���������� ����
	if (loginedUser->_writePost() == true)
	{
		acs = new AcsPublic;
		// ���� ����Ʈ�� ����
	}
	else
	{
		acs = new AcsPrivate;
		// �����
	}
	newPost->setAcs(acs); // �������� ����

	for (int i = 0; i < loginedUser->getFlist().size(); i++)
	{
		newOb.push_back(loginedUser->getFlist().at(i));
	} // for�� ������ newOb���ٰ� �� �Ű��� ����! < ��Ӱ����̹Ƿ� �̷��� �Ű��־�� �Ѵٰ� ��(ģ���� ����Ʈ�� �� ��������Ʈ ������Ʈ �ϴ� ����)

	newPost->getAcs()->update(newOb, newPost->getud(), newPost->getitid(), newPost->getct());
	// ������Ʈ �Ѵ�. timeline ������Ʈ ��!	
	loginedUser->addPostToMyPosts(newPost);
	// mypost���� �߰�!
	cout << "���� ���������� �߰��Ͽ����ϴ�!" << endl;
}

void App::printMyPosting()
{
	if (!loginedUser->getMyPost().size())
	{
		cout << "�ۼ��� ���� �����ϴ�!" << endl;
		return;
	}
	string name;
	for (int i = 0; i < loginedUser->getMyPost().size(); i++)
	{
		Post* temp = loginedUser->getMyPost().at(i);
		if (temp->getud() == userList.at(i)->getId())
		{
			name = userList.at(i)->getattrs()["�̸�"];
		}
		cout << "�ۼ��� :" << name << endl;
		cout << "���� :" << temp->getct() << endl;
	}
}
// ���� �� ���̴ϱ� ���� �ۼ��� ���ص� �� ��

void App::printTimeline()
{
	if (!loginedUser->getTimeline().size())
	{
		cout << "Ÿ�Ӷ��ο� �ö�� ���� �����ϴ�!" << endl;
		return;
	}
	string name;
	for (int i = 0; i < loginedUser->getTimeline().size(); i++)
	{
		Post* temp = loginedUser->getTimeline().at(i);
		if (temp->getud() == userList.at(i)->getId())
		{
			name = userList.at(i)->getattrs()["�̸�"];
		}
		cout << "�ۼ��� : " << name << endl;
		cout << "���� : " << temp->getct() << endl;
	}
}

void App::MessageTab()
{
	while (1)
	{
		cout << endl;
		cout << "�� �޽��� �� ��" << endl;
		cout << "1. �޽��� ������" << endl;
		cout << "2. ä�ù� ����" << endl;
		cout << "0. �ڷΰ���" << endl;

		int command = GetCommand(3);
		switch (command)
		{
		case 1:
			cout << endl;
			sendMessage();
			break;
		case 2:
			cout << endl;
			printMessages();
			break;
		case 0:
			return;
		}
	}
}

void App::sendMessage()
// �޽����� ģ�����׸� ���� �� �ִ�.
{
	cout << "ģ�� ���" << endl;
	cout << "�ѤѤѤѤѤѤѤѤѤѤѤѤѤ�" << endl;
	for (int i = 0; i < loginedUser->getFlist().size(); i++)
	{
		cout << i + 1 << ".	" << loginedUser->getFlist()[i]->getattrs()["�̸�"] << endl;
		cout << "���� : " << loginedUser->getFlist()[i]->getattrs()["����"] << endl;
		cout << "���� : " << loginedUser->getFlist()[i]->getattrs()["����"] << endl;
		cout << "�б� : " << loginedUser->getFlist()[i]->getattrs()["�б�"] << endl;
		cout << "���� : " << loginedUser->getFlist()[i]->getattrs()["����"] << endl;
	}
	cout << "0. �ڷΰ���" << endl;
	int command = GetCommand(loginedUser->getFlist().size());
	if (command == 0)
	{
		return;
	}

	Message* temp = new Message;
	messagenum += 1;
	temp->setContentByKB();
	temp->setItemID(messagenum);
	temp->setUserID(loginedUser->getId());

	User* ToUser = new User;
	ToUser = loginedUser->getFlist()[command - 1];

	loginedUser->addToSendedMessage(temp);
	ToUser->addToRecievedMessage(temp);
	cout << "�޽����� ���������� �����Ͽ����ϴ�!" << endl;

	//string name;
	//vector<int> Id;
	//User* selecUser = new User; // �޽����� ������� (���� ���)
	//int idx = 0;
	//cout << "�޽����� ���� ����� �̸� : ";
	//cin >> name;

	//for (int i = 0; i < loginedUser->getFlist().size(); i++)
	//{
	//	if (loginedUser->getFlist()[i]->getattrs()["�̸�"] == name)
	//	{
	//		++idx;
	//		cout << idx << " .\t" << loginedUser->getFlist()[i]->getattrs()["�̸�"] << endl;
	//		cout << "\t" << "���� : " << loginedUser->getFlist()[i]->getattrs()["����"] << endl;
	//		cout << "\t" << "���� : " << loginedUser->getFlist()[i]->getattrs()["����"] << endl;
	//		cout << "\t" << "�б� : " << loginedUser->getFlist()[i]->getattrs()["�б�"] << endl;
	//		cout << "\t" << "���� : " << loginedUser->getFlist()[i]->getattrs()["����"] << endl;
	//		Id.push_back(userList.at(i)->getId()); // ���� ������ ���̵� �ӽ� ����	
	//	}
	//}

	//if (Id.empty())
	//{
	//	cout << "ģ����Ͽ� ��ġ�ϴ� ����ڰ� �����ϴ�!" << endl;
	//	return;
	//}
	//else
	//{
	//	cout << "0. �ڷΰ���" << endl;
	//}
	//	cout << "�޽����� ���� ��� ���� : ";
	//int num;
	//cin >> num;
	//if (num == 0)
	//{
	//	return;
	//}
	//else
	//{
	//	for (int i = 0; i < loginedUser->getFlist().size(); i++)
	//	{
	//		if (loginedUser->getFlist()[i]->getId() == Id[num - 1])
	//		{
	//			selecUser = loginedUser->getFlist()[i];
	//			// selecUser�� ������ ģ���� �ּҸ� ��´�.
	//		}
	//	}
	//}

	//Message* newMessage = new Message;
	//newMessage->setContentByKB();
	//newMessage->setUserID(loginedUser->getId());
	//messagenum += 1;
	//newMessage->setItemID(messagenum);

	//loginedUser->addToSendedMessage(newMessage);
	//selecUser->addToRecievedMessage(newMessage); // selecUser : �޴� ���
}

void App::printMessages()
{
	cout << "�� �޽��� ����Ʈ �� ��" << endl;
	if (loginedUser->getFlist().size() == 0)
	{
		cout << "������� ģ������Ʈ�� ������ϴ�!" << endl;
		return;
	}
	cout << "ä�ù� ����" << endl;
	for (int i = 0; i < loginedUser->getFlist().size(); i++)
	{
		cout << i + 1 << " ." << loginedUser->getFlist()[i]->getattrs()["�̸�"] << endl;
	}
	int command = GetCommand((int)loginedUser->getFlist().size());

	User* selecUser = new User;
	selecUser = loginedUser->getFlist()[command - 1];

	// �����Ұ� : �ð������� ����ؾ� ��(���ö� ������ �ð������� �����⿡ ���������
	// �����Ұ� : ī��� �������� ������ �����ؾ� ������� �߰��߰��� ������
	// �ذ��� : Sorting!!
	vector<Message*> PrintMessage;

	// �� ������� �ְ���� �޽����� ������� ����ó�� �ؾ���
	for (int i = 0; i < loginedUser->getrecievedmessage().size(); i++) // �׻������ �ְ���� �޽��� �� "����"�޽���
	{
		if (loginedUser->getrecievedmessage().at(i)->getUserID() == selecUser->getId())
		{
			PrintMessage.push_back(loginedUser->getrecievedmessage()[i]);
		}
	}

	for (int i = 0; i < selecUser->getrecievedmessage().size(); i++)
	{
		if (selecUser->getrecievedmessage().at(i)->getUserID() == loginedUser->getId())
		{
			PrintMessage.push_back(selecUser->getrecievedmessage()[i]);
		}
	}

	if (PrintMessage.size() == 0)
	{
		cout << "�ְ���� ��ȭ�� �����ϴ�. " << selecUser->getattrs()["�̸�"] << "�� ���� ��ȭ�� �����غ�����!" << endl;
		return;
	} // �ְ���� ��ȭ�� ���� ����� ����ó��

	for (int i = 0; i < PrintMessage.size() - 1; i++)
	{
		for (int j = 1; j < PrintMessage.size() - i; j++)
			if (PrintMessage[j - 1]->getItemID() > PrintMessage[j]->getItemID())
			{
				Message* temp;
				temp = PrintMessage[j - 1];
				PrintMessage[j - 1] = PrintMessage[j];
				PrintMessage[j] = temp;
			}
	}
	// BubbleSort�� �̿��� ����

	for (int i = 0; i < PrintMessage.size(); i++)
	{
		if (PrintMessage[i]->getUserID() == loginedUser->getId())
		{
			cout << "�� : " << PrintMessage[i]->getContent() << endl;
		}
		else
		{
			cout << selecUser->getattrs()["�̸�"] << " : " << PrintMessage[i]->getContent() << endl;
		}

	}

	// ����ȣ���� ��ȭ �� ��������Ʈ, ��������Ʈ ��� �� ���Ϳ� ���Ƴ־ �������
	// ���Ϳ� ���Ƴ����� �����۾��̵� ����������� 0��°ĭ���� ä���ִ� �ڵ� �ۼ�
	// 

	// ���� ģ������Ʈ �� ����ȣ ����?
	// �α����� ������ �����޽��� �� ����ȣ�ΰ� ���
	// �α����� ������ �����޽��� �� ����ȣ�ΰ� ���
}

void App::FriendTab()
{
	while (1)
	{
		cout << endl;
		cout << "�� ģ�� �� ��" << endl;
		cout << "1. ģ�� ��õ �ޱ� " << endl;
		cout << "2. ģ�� ��û �ϱ�" << endl;
		cout << "3. ģ�� ��û ����" << endl;
		cout << "4. ģ�� ��û ����" << endl;
		cout << "0. �ڷ� ����" << endl;

		int command = GetCommand(4);

		switch (command)
		{
		case 1:
			cout << endl;
			friendRecommendation();
			break;
		case 2:
			cout << endl;
			requestFriend();
			break;
		case 3:
			cout << endl;
			acceptFriend();
			break;
		case 4:
			cout << endl;
			rejectFriend();
			break;
		case 0:
			return;
		}
	}
}

void App::friendRecommendation()
{
	//vector<User*> Friends = loginedUser->getFlist();
	//int flag = 0; // flag�� 3�̻��̸� ��õ!
	//User* RecomandUser = new User;
	//vector<User*> Recomandlist;
	//for (int i = 0; i < Friends.size(); i++)
	//{
	//	Friends.at(i)->getFlist(); // ģ����� �� i��°�� �ִ� ģ���� ģ�����(ģ��'s ģ�����)
	//	for (int j = 0; j < Friends.at(j)->getFlist().size(); j++)
	//	{
	//		if (loginedUser->getattrs()["�̸�"] == Friends.at(i)->getFlist().at(j)->getattrs()["�̸�"])
	//		{
	//			flag += 1;
	//		}
	//		else if (loginedUser->getattrs()["����"] == Friends.at(i)->getFlist().at(j)->getattrs()["����"])
	//		{
	//			flag += 1;
	//		}
	//		else if (loginedUser->getattrs()["����"] == Friends.at(i)->getFlist().at(j)->getattrs()["����"])
	//		{
	//			flag += 1;
	//		}
	//		else if (loginedUser->getattrs()["�б�"] == Friends.at(i)->getFlist().at(j)->getattrs()["�б�"])
	//		{
	//			flag += 1;
	//		}
	//		else if (loginedUser->getattrs()["����"] == Friends.at(i)->getFlist().at(j)->getattrs()["����"])
	//		{
	//			flag += 1;
	//		}
	//		if (flag >= 3)
	//		{
	//			RecomandUser = Friends.at(i)->getFlist().at(j);
	//			// RecommandUser�� ��õ���� ģ����!
	//			Recomandlist.push_back(RecomandUser);
	//		}
	//	}

	//	for (int i = 0; i < Recomandlist.size(); i++)
	//	{
	//		cout << i + 1 << " ." << Recomandlist[i]->getattrs()["�̸�"];
	//		cout << " ���� : " << Recomandlist[i]->getattrs()["����"];
	//		cout << " ���� : " << Recomandlist[i]->getattrs()["����"];
	//		cout << " �б� : " << Recomandlist[i]->getattrs()["�б�"];
	//		cout << " ���� : " << Recomandlist[i]->getattrs()["����"] << endl;
	//	}
	//	// ��õģ������� ����!
	//	cout << "��õ ģ���� ģ�� �߰� �Ͻðڽ��ϱ�? " << endl;
	//	int num1;
	//	cout << "0. �ڷΰ���" << endl;
	//	cout << "1. ��" << endl;
	//	if (num1 == 0)
	//	{
	//		return;
	//	}
	//	else if (num1 == 1)
	//	{
	//		int num;
	//		cout << "�߰��� ģ�� ���� : ";
	//		cin >> num;
	//		loginedUser->addFriend(Recomandlist[num - 1]); // �߰��� ģ���� �ּҰ� ��� ĭ(�ε���)
	//		// ��õ ģ�� �߰� �Ϸ�
	//		cout << "ģ���� �߰��Ͽ����ϴ�!" << endl;
	//	}
	//}

	while (1)
	{
		cout << "�� ģ�� ��õ �� ��" << endl;
		cout << "1. �� ģ���� ģ���� ��õ�ޱ�" << endl;
		cout << "2. �������� ���� ģ���� ��õ�ޱ�" << endl;
		cout << "0. �ڷ� ����" << endl;
		int command = GetCommand(2);
		switch (command)
		{
		case 1:
			cout << endl;
			friendType1();
			break;
		case 2:
			cout << endl;
			friednType2();
			break;
		case 0:
			return;
		}
	}

}
void App::friendType1()
{
	vector<User*> RecommandList1; // ��õ ���(1)

	for (int i = 0; i < loginedUser->getFlist().size(); i++) // ģ������Ʈ
	{
		for (int j = 0; j < loginedUser->getFlist().at(i)->getFlist().size(); j++) // ģ������Ʈ�� �ִ� ģ������ ģ������Ʈ
		{
			if (loginedUser != loginedUser->getFlist().at(i)->getFlist().at(j)) // �ٸ� ģ������ ģ���� ���Ե� "��"�� ����(����ó��)
			{
				RecommandList1.push_back(loginedUser->getFlist().at(i)->getFlist().at(j));
			}
		}
	}
	if (RecommandList1.size() == 0)
	{
		cout << "��õ�� ģ���� �����ϴ�!" << endl;
		return;
	}

	for (int i = 0; i < RecommandList1.size(); i++)
	{
		cout << i + 1 << " ." << RecommandList1[i]->getattrs()["�̸�"];
		cout << " ���� : " << RecommandList1[i]->getattrs()["����"];
		cout << " ���� : " << RecommandList1[i]->getattrs()["����"];
		cout << " �б� : " << RecommandList1[i]->getattrs()["�б�"];
		cout << " ���� : " << RecommandList1[i]->getattrs()["����"] << endl;
	}
	cout << endl;
}

void App::friednType2()
// �ڱ��ڽ��� �ȶ߰��ؾ��� < ������ �����ϵ�
{
	vector<User*> RecommandList2; // ��õ ���(2)
	
	for (int i = 0; i < userList.size(); i++)
	{
		if (userList[i]->getId() == loginedUser->getId())
		{
			continue;
			// ���� �ڱ��ڽ��̸� �ǳʶٰ� �������� ��������!
		}
		int flag = 0; // �Ӽ��� ��ġ ���� Ȯ��
		if (loginedUser->getattrs()["�̸�"] == userList.at(i)->getattrs()["�̸�"])
		{
			flag += 1;
		}
		if (loginedUser->getattrs()["����"] == userList.at(i)->getattrs()["����"])
		{
			flag += 1;
		}
		if (loginedUser->getattrs()["����"] == userList.at(i)->getattrs()["����"])
		{
			flag += 1;
		}
		if (loginedUser->getattrs()["�б�"] == userList.at(i)->getattrs()["�б�"])
		{
			flag += 1;
		}
		if (loginedUser->getattrs()["����"] == userList.at(i)->getattrs()["����"])
		{
			flag += 1;
		}
		if (flag >= 3)
		{
			RecommandList2.push_back(userList.at(i));
			// �������� ���� �̻��� ģ���� ���Ϳ� ����
		}
	}
	if (!RecommandList2.size())
	{
		cout << "��õ�� ģ���� �����ϴ�!" << endl;
		return;
	}
	// ����ó��

	for (int i = 0; i < RecommandList2.size(); i++)
	{
		cout << "\n" << i + 1 << " ." << RecommandList2[i]->getattrs()["�̸�"] << endl;
		cout << "���� : " << RecommandList2[i]->getattrs()["����"] << endl;
		cout << "���� : " << RecommandList2[i]->getattrs()["����"] << endl;
		cout << "�б� : " << RecommandList2[i]->getattrs()["�б�"] << endl;
		cout << "���� : " << RecommandList2[i]->getattrs()["����"] << endl;
	}
	cout << endl;
}
// ģ�� ��õ 
// �Ӽ� ���� 3�� �̻� ������ ������� ��õ ����
// ������ �Ӽ��� ���Ͽ� �񱳷����� �����.
// ���� ������ true �ٸ��� false�� ����
// true�� 3���̻� ������ ��õ!

void App::requestFriend()
{
	string name;
	cout << "ģ�� ��û�� ����� �̸��� �Է��ϼ��� : ";
	cin >> name;
	vector<int> Id;
	int idx = 1;


	cout << "0. �ڷΰ���" << endl;
	for (int i = 0; i < userList.size(); i++)
	{
		if (userList.at(i)->getattrs()["�̸�"] == name)
		{
			cout << idx++ << ". " << "�̸� : " << userList.at(i)->getattrs()["�̸�"];
			cout << " ����: " << userList.at(i)->getattrs()["����"];
			cout << " ����: " << userList.at(i)->getattrs()["����"];
			cout << " �б�: " << userList.at(i)->getattrs()["�б�"];
			cout << " ����: " << userList.at(i)->getattrs()["����"] << endl;
			Id.push_back(userList.at(i)->getId()); // ã�� ģ���� ���̵� ���� �ӽú���
		}
		// ���� �̸��� ���� ����� ��� (�������� ����)
	}
	if (Id.size() == 0)
	{
		cout << "��ġ�ϴ� ����ڰ� �����ϴ�!" << endl;
		return;
	}
	int num;
	cout << "ģ�� ��û�� ��� ���� : ";
	cin >> num;
	if (num == 0)
	{
		return; // �ڷΰ���
	}

	else
	{
		for (int i = 0; i < userList.size(); i++)
		{
			if (userList.at(i)->getId() == Id[num - 1])
			{
				for (int k = 0; k < loginedUser->getFlist().size(); k++)
				{
					if (loginedUser->getFlist()[k] == userList[i])
					{
						cout << "�̹� " << userList[i]->getattrs()["�̸�"] << "�԰� ģ���Դϴ�!" << endl;
						return;

					}

				}
				userList.at(i)->addRecievedFR(loginedUser);
				// ģ���� ģ���� ��ûģ�� ���Ϳ� �α����� ����� ����
				cout << "ģ���߰� �Ϸ�!" << endl;
			}
		}
	}
}

void App::acceptFriend()
{
	if (loginedUser->getrecievedFR().size() == 0)
	{
		cout << "���� ģ�� ����� �����ϴ�!" << endl;
		return;
	}
	cout << "���� ģ�� ��û ���" << endl;
	for (int i = 0; i < loginedUser->getrecievedFR().size(); i++)
	{
		cout << endl;
		cout << i + 1 << "	." << loginedUser->getrecievedFR()[i]->getattrs()["�̸�"] << endl;
		cout << "���� : " << loginedUser->getrecievedFR()[i]->getattrs()["����"] << endl;
		cout << "���� : " << loginedUser->getrecievedFR()[i]->getattrs()["����"] << endl;
		cout << "�б� : " << loginedUser->getrecievedFR()[i]->getattrs()["�б�"] << endl;
		cout << "���� : " << loginedUser->getrecievedFR()[i]->getattrs()["����"] << endl;
	}

	int command = GetCommand(loginedUser->getrecievedFR().size());
	if (command == 0)
	{
		return; // �ڷΰ���
	}
	else
	{
		command -= 1; // �����Ҷ� +1 �ؼ� ���������Ƿ�
		User* selecUser = new User;
		selecUser = loginedUser->getrecievedFR()[command];
		loginedUser->addFriend(selecUser);
		selecUser->addFriend(loginedUser);
		cout << "�������� " << loginedUser->getrecievedFR()[command]->getattrs()["�̸�"] << "�԰� ģ���Դϴ�!" << endl;
		loginedUser->EraseRecieved(command);
	}
}

void App::rejectFriend()
{
	if (loginedUser->getrecievedFR().size() == 0)
	{
		cout << "���� ģ�� ����� �����ϴ�!" << endl;
		return;
	}
	cout << "���� ģ�� ��û ���" << endl;
	for (int i = 0; i < loginedUser->getrecievedFR().size(); i++)
	{
		cout << endl;
		cout << i + 1 << "	." << loginedUser->getrecievedFR()[i]->getattrs()["�̸�"] << endl;
		cout << "���� : " << loginedUser->getrecievedFR()[i]->getattrs()["����"] << endl;
		cout << "���� : " << loginedUser->getrecievedFR()[i]->getattrs()["����"] << endl;
		cout << "�б� : " << loginedUser->getrecievedFR()[i]->getattrs()["�б�"] << endl;
		cout << "���� : " << loginedUser->getrecievedFR()[i]->getattrs()["����"] << endl;
	}

	int command = GetCommand(loginedUser->getrecievedFR().size());
	if (command == 0)
	{
		return; // �ڷΰ���
	}
	else
	{
		command -= 1; // �����Ҷ� +1 �ؼ� ���������Ƿ�
		User* selecUser = new User;
		selecUser = loginedUser->getrecievedFR()[command];
		cout << loginedUser->getrecievedFR()[command]->getattrs()["�̸�"] << "���� ģ����û�� �����߽��ϴ�!" << endl;
		loginedUser->EraseRecieved(command);
	}
}

int App::GetCommand(int maxCommand)
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