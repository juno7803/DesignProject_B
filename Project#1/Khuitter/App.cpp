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
	cout << "┌─────────────────────────────────┐" << endl;
	cout << "│                                                                  │" << endl;
	cout << "│                       ▶    ⓚhuitter    ◀                      │" << endl;
	cout << "│                                                                  │" << endl;
	cout << "└─────────────────────────────────┘" << endl;
	InitialMenu();
}

void App::StartMenu()
{
	while (1)
	{
		cout << "\n사용자 : " << loginedUser->getattrs()["이름"] << endl;
		cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
		cout << "1. 포스트 탭" << endl;
		// 글 추가
		// 내 글 보기
		// 타임라인 보기

		cout << "2. 메시지 탭" << endl;
		// 메시지 보내기
		// 1.받은 메시지 보기
		// 2.보낸 메시지 보기
		// 3.카톡방 처럼 보이기

		cout << "3. 친구 탭" << endl;
		// 1. 친구 추천받기
		// (1) 친구들의 친구들 전부 출력(약간 보완하고 싶음)
		// (2) 속성이 세개이상 같은 친구 출력
		// *****(질문) 검색기능만 할지 여기서 바로 추가할지
		// (예외처리)
		// (1) 이미 추가된 친구는 출력하면 안됨

		// 2. 친구 추가하기
		// (예외처리)
		// 1. 이미 추가된 친구는 추가 불가
		// 2. 같은 친구가 중복으로 추가되면 안된다.
		cout << "0. 뒤로가기" << endl;

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
			// 아이디가 일치하는 유저의 주소 리턴
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
		ofs << userList[i]->getId() << "\t"; // 유저 아이디
		ofs << userList[i]->getFlist().size() << "\t"; // 친구 카운트
		for (int j = 0; j < userList[i]->getFlist().size(); j++)
		{
			ofs << userList[i]->getFlist()[j]->getId(); // 친구들의 아이디
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
		ofs << userList[i]->getattrs()["이름"] << "\t";
		ofs << userList[i]->getattrs()["나이"] << "\t";
		ofs << userList[i]->getattrs()["성별"] << "\t";
		ofs << userList[i]->getattrs()["학교"] << "\t";
		ofs << userList[i]->getattrs()["지역"];
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
	// 받는아이디는 어떻게 해야할지 고민
	// 중복되는 포스트 어떻게 저장할지 고민
	ofstream ofs("message.txt");
	flag = 0;
	// 받은메시지만 올리면 된다! < 이유 : 내 입장이므로, 받은 사람의 아이디와 보낸사람의 아이디가 있다.
	for (int i = 0; i < userList.size(); i++)
	{
		if (userList[i]->getrecievedmessage().size() == 0)
		{
			continue;
		}
		// 컨티뉴로 건너뛰다가 이제 받은메시지가 있는 사람의 처음에 도달했다.
		// 처음만 엔드라인 안해야함. 그 처음을 어떻게 표시하지?

		// 드디어 컨티뉴에 안막히고 넘어왔을때 flag는 0이고 다음번부턴 엔드라인이 필요하므로 플래그를 1 증가시킨다.
		// flag 각각 해줘야한다. 왜냐면 전역변수이기 때문에 post에서 바뀌면 여기도 바뀌어 있으므로!!
		// <해결책>
		// flagp(post) , flagm(message), flagt(timeline) 각각 만들었음
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
			ofs << userList[i]->getrecievedmessage()[j]->getUserID() << "\t"; // 누가 보낸건지 (UserID)
			ofs << userList[i]->getId() << "\t"; // 누구에게 보낸건지 (toUserID)
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
		if (flag != 0) // 이 코드가 틀림
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

	while (!ifs1.eof())// 파일이 끝날때 까지
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
			// friendList 벡터에 저장(추가)
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
			// reciecedFriendRequest에 저장(추가)
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
		User* CurUser = new User; // 유저형 임시 객체

		CurUser->setId(userId);
		CurUser->setPw(pw);
		CurUser->setAttrToKeyValueMap("이름", username);
		CurUser->setAttrToKeyValueMap("나이", attr1);
		CurUser->setAttrToKeyValueMap("성별", attr2);
		CurUser->setAttrToKeyValueMap("학교", attr3);
		CurUser->setAttrToKeyValueMap("지역", attr4);

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
		// 동적할당 하는 이유는? -> 안하고 Post포인터형으로 만들면 NULL이기 때문에 동적할당으로 객체를 인스턴스화 해줘야한다!
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
		Timeline->setContent(content); // 그럼 꼭 필요한건 아닌듯?
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
		cout << "Khuitter에 어서오세요" << endl;
		cout << "1. 로그인 " << endl;
		cout << "2. 로그아웃" << endl;
		cout << "0. 종료" << endl;
		// 로그인 성공하면 StartMenu() 불러온다.
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
	//loginedUser = 로그인한 유저주소;

	string name, pw;

	cout << "이름 : ";
	cin >> name;
	cout << "비밀번호 : ";
	cin >> pw;

	for (int i = 0; i < userList.size(); i++)
	{
		if ((userList.at(i)->getattrs()["이름"]) == name) // 같은 이름을 찾았다!
		{
			if (userList.at(i)->getPw() == pw)
			{
				cout << "로그인에 성공하였습니다!" << endl;
				loginedUser = userList.at(i);
				StartMenu(); // 시~작!
				return; // 여기서 리턴안하니까 밑으로 내려가더라..
			}
			else
			{
				cout << "비밀번호가 틀렸습니다!" << endl;
				return;
			}
		}
	}
	cout << "일치하는 이름을 가진 사용자가 없습니다!" << endl;
	return;

}

void App::logout()
{
	loginedUser = NULL;
	cout << "성공적으로 로그아웃 되었습니다!" << endl;
}

void App::PostTab()
{
	while (1)
	{
		cout << endl;
		cout << "◁ 포스트 탭 ▷" << endl;
		cout << "1. 포스트 추가" << endl;
		cout << "2. 내글 보기" << endl;
		cout << "3. 타임라인 보기" << endl;
		cout << "0. 뒤로 가기" << endl;

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
	// 내가 글을 쓴다!
	// case 1 공개 포스트를 선택하자
	Post* newPost = new Post;
	Accessibility* acs = newPost->getAcs();
	vector<Observer*> newOb;

	newPost->setUserID(loginedUser->getId()); // 아이디 저장
	newPost->setContentByKB(); // 내용 저장
	postnum += 1;
	newPost->setItemID(postnum); // 포스트 아이디 저장, 순차적으로 증가
	if (loginedUser->_writePost() == true)
	{
		acs = new AcsPublic;
		// 공개 포스트로 설정
	}
	else
	{
		acs = new AcsPrivate;
		// 비공개
	}
	newPost->setAcs(acs); // 공개여부 저장

	for (int i = 0; i < loginedUser->getFlist().size(); i++)
	{
		newOb.push_back(loginedUser->getFlist().at(i));
	} // for문 돌려서 newOb에다가 다 옮겨준 다음! < 상속관계이므로 이렇게 옮겨주어야 한다고 함(친구들 리스트에 내 공개포스트 업데이트 하는 과정)

	newPost->getAcs()->update(newOb, newPost->getud(), newPost->getitid(), newPost->getct());
	// 업데이트 한다. timeline 업데이트 끝!	
	loginedUser->addPostToMyPosts(newPost);
	// mypost에도 추가!
	cout << "글을 성공적으로 추가하였습니다!" << endl;
}

void App::printMyPosting()
{
	if (!loginedUser->getMyPost().size())
	{
		cout << "작성한 글이 없습니다!" << endl;
		return;
	}
	string name;
	for (int i = 0; i < loginedUser->getMyPost().size(); i++)
	{
		Post* temp = loginedUser->getMyPost().at(i);
		if (temp->getud() == userList.at(i)->getId())
		{
			name = userList.at(i)->getattrs()["이름"];
		}
		cout << "작성자 :" << name << endl;
		cout << "내용 :" << temp->getct() << endl;
	}
}
// 내가 쓴 글이니까 굳이 작성자 안해도 될 듯

void App::printTimeline()
{
	if (!loginedUser->getTimeline().size())
	{
		cout << "타임라인에 올라온 글이 없습니다!" << endl;
		return;
	}
	string name;
	for (int i = 0; i < loginedUser->getTimeline().size(); i++)
	{
		Post* temp = loginedUser->getTimeline().at(i);
		if (temp->getud() == userList.at(i)->getId())
		{
			name = userList.at(i)->getattrs()["이름"];
		}
		cout << "작성자 : " << name << endl;
		cout << "내용 : " << temp->getct() << endl;
	}
}

void App::MessageTab()
{
	while (1)
	{
		cout << endl;
		cout << "◁ 메시지 탭 ▷" << endl;
		cout << "1. 메시지 보내기" << endl;
		cout << "2. 채팅방 보기" << endl;
		cout << "0. 뒤로가기" << endl;

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
// 메시지는 친구한테만 보낼 수 있다.
{
	cout << "친구 목록" << endl;
	cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
	for (int i = 0; i < loginedUser->getFlist().size(); i++)
	{
		cout << i + 1 << ".	" << loginedUser->getFlist()[i]->getattrs()["이름"] << endl;
		cout << "성별 : " << loginedUser->getFlist()[i]->getattrs()["성별"] << endl;
		cout << "나이 : " << loginedUser->getFlist()[i]->getattrs()["나이"] << endl;
		cout << "학교 : " << loginedUser->getFlist()[i]->getattrs()["학교"] << endl;
		cout << "지역 : " << loginedUser->getFlist()[i]->getattrs()["지역"] << endl;
	}
	cout << "0. 뒤로가기" << endl;
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
	cout << "메시지를 성공적으로 전송하였습니다!" << endl;

	//string name;
	//vector<int> Id;
	//User* selecUser = new User; // 메시지를 받을사람 (보낼 대상)
	//int idx = 0;
	//cout << "메시지를 보낼 사람의 이름 : ";
	//cin >> name;

	//for (int i = 0; i < loginedUser->getFlist().size(); i++)
	//{
	//	if (loginedUser->getFlist()[i]->getattrs()["이름"] == name)
	//	{
	//		++idx;
	//		cout << idx << " .\t" << loginedUser->getFlist()[i]->getattrs()["이름"] << endl;
	//		cout << "\t" << "성별 : " << loginedUser->getFlist()[i]->getattrs()["성별"] << endl;
	//		cout << "\t" << "나이 : " << loginedUser->getFlist()[i]->getattrs()["나이"] << endl;
	//		cout << "\t" << "학교 : " << loginedUser->getFlist()[i]->getattrs()["학교"] << endl;
	//		cout << "\t" << "지역 : " << loginedUser->getFlist()[i]->getattrs()["지역"] << endl;
	//		Id.push_back(userList.at(i)->getId()); // 보낼 유저의 아이디 임시 저장	
	//	}
	//}

	//if (Id.empty())
	//{
	//	cout << "친구목록에 일치하는 사용자가 없습니다!" << endl;
	//	return;
	//}
	//else
	//{
	//	cout << "0. 뒤로가기" << endl;
	//}
	//	cout << "메시지를 보낼 사람 선택 : ";
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
	//			// selecUser에 선택한 친구의 주소를 담는다.
	//		}
	//	}
	//}

	//Message* newMessage = new Message;
	//newMessage->setContentByKB();
	//newMessage->setUserID(loginedUser->getId());
	//messagenum += 1;
	//newMessage->setItemID(messagenum);

	//loginedUser->addToSendedMessage(newMessage);
	//selecUser->addToRecievedMessage(newMessage); // selecUser : 받는 사람
}

void App::printMessages()
{
	cout << "◁ 메시지 프린트 탭 ▷" << endl;
	if (loginedUser->getFlist().size() == 0)
	{
		cout << "사용자의 친구리스트가 비었습니다!" << endl;
		return;
	}
	cout << "채팅방 들어가기" << endl;
	for (int i = 0; i < loginedUser->getFlist().size(); i++)
	{
		cout << i + 1 << " ." << loginedUser->getFlist()[i]->getattrs()["이름"] << endl;
	}
	int command = GetCommand((int)loginedUser->getFlist().size());

	User* selecUser = new User;
	selecUser = loginedUser->getFlist()[command - 1];

	// 생각할것 : 시간순으로 출력해야 함(들어올때 어차피 시간순으로 들어오기에 상관없을듯
	// 생각할것 : 카톡방 형식으로 띄우려면 어케해야 답장까지 중간중간에 넣을까
	// 해결방법 : Sorting!!
	vector<Message*> PrintMessage;

	// 그 사람과의 주고받은 메시지가 없을경우 예외처리 해야함
	for (int i = 0; i < loginedUser->getrecievedmessage().size(); i++) // 그사람과의 주고받은 메시지 중 "받은"메시지
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
		cout << "주고받은 대화가 없습니다. " << selecUser->getattrs()["이름"] << "님 과의 대화를 시작해보세요!" << endl;
		return;
	} // 주고받은 대화가 없을 경우의 예외처리

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
	// BubbleSort를 이용한 정렬

	for (int i = 0; i < PrintMessage.size(); i++)
	{
		if (PrintMessage[i]->getUserID() == loginedUser->getId())
		{
			cout << "나 : " << PrintMessage[i]->getContent() << endl;
		}
		else
		{
			cout << selecUser->getattrs()["이름"] << " : " << PrintMessage[i]->getContent() << endl;
		}

	}

	// 이준호와의 대화 중 보낸리스트, 받은리스트 모두 한 벡터에 몰아넣어서 출력하자
	// 벡터에 몰아넣을때 아이템아이디 작은순서대로 0번째칸부터 채워넣는 코드 작성
	// 

	// 만약 친구리스트 중 이준호 선택?
	// 로그인한 유저의 보낸메시지 중 이준호인것 출력
	// 로그인한 유저의 받은메시지 중 이준호인것 출력
}

void App::FriendTab()
{
	while (1)
	{
		cout << endl;
		cout << "◁ 친구 탭 ▷" << endl;
		cout << "1. 친구 추천 받기 " << endl;
		cout << "2. 친구 신청 하기" << endl;
		cout << "3. 친구 요청 수락" << endl;
		cout << "4. 친구 요청 삭제" << endl;
		cout << "0. 뒤로 가기" << endl;

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
	//int flag = 0; // flag가 3이상이면 추천!
	//User* RecomandUser = new User;
	//vector<User*> Recomandlist;
	//for (int i = 0; i < Friends.size(); i++)
	//{
	//	Friends.at(i)->getFlist(); // 친구목록 중 i번째에 있는 친구의 친구목록(친구's 친구목록)
	//	for (int j = 0; j < Friends.at(j)->getFlist().size(); j++)
	//	{
	//		if (loginedUser->getattrs()["이름"] == Friends.at(i)->getFlist().at(j)->getattrs()["이름"])
	//		{
	//			flag += 1;
	//		}
	//		else if (loginedUser->getattrs()["나이"] == Friends.at(i)->getFlist().at(j)->getattrs()["나이"])
	//		{
	//			flag += 1;
	//		}
	//		else if (loginedUser->getattrs()["성별"] == Friends.at(i)->getFlist().at(j)->getattrs()["성별"])
	//		{
	//			flag += 1;
	//		}
	//		else if (loginedUser->getattrs()["학교"] == Friends.at(i)->getFlist().at(j)->getattrs()["학교"])
	//		{
	//			flag += 1;
	//		}
	//		else if (loginedUser->getattrs()["지역"] == Friends.at(i)->getFlist().at(j)->getattrs()["지역"])
	//		{
	//			flag += 1;
	//		}
	//		if (flag >= 3)
	//		{
	//			RecomandUser = Friends.at(i)->getFlist().at(j);
	//			// RecommandUser가 추천받은 친구임!
	//			Recomandlist.push_back(RecomandUser);
	//		}
	//	}

	//	for (int i = 0; i < Recomandlist.size(); i++)
	//	{
	//		cout << i + 1 << " ." << Recomandlist[i]->getattrs()["이름"];
	//		cout << " 나이 : " << Recomandlist[i]->getattrs()["나이"];
	//		cout << " 성별 : " << Recomandlist[i]->getattrs()["성별"];
	//		cout << " 학교 : " << Recomandlist[i]->getattrs()["학교"];
	//		cout << " 지역 : " << Recomandlist[i]->getattrs()["지역"] << endl;
	//	}
	//	// 추천친구목록을 띄운다!
	//	cout << "추천 친구를 친구 추가 하시겠습니까? " << endl;
	//	int num1;
	//	cout << "0. 뒤로가기" << endl;
	//	cout << "1. 네" << endl;
	//	if (num1 == 0)
	//	{
	//		return;
	//	}
	//	else if (num1 == 1)
	//	{
	//		int num;
	//		cout << "추가할 친구 선택 : ";
	//		cin >> num;
	//		loginedUser->addFriend(Recomandlist[num - 1]); // 추가할 친구의 주소가 담긴 칸(인덱스)
	//		// 추천 친구 추가 완료
	//		cout << "친구를 추가하였습니다!" << endl;
	//	}
	//}

	while (1)
	{
		cout << "◁ 친구 추천 탭 ▷" << endl;
		cout << "1. 내 친구의 친구들 추천받기" << endl;
		cout << "2. 공통점을 가진 친구들 추천받기" << endl;
		cout << "0. 뒤로 가기" << endl;
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
	vector<User*> RecommandList1; // 추천 방식(1)

	for (int i = 0; i < loginedUser->getFlist().size(); i++) // 친구리스트
	{
		for (int j = 0; j < loginedUser->getFlist().at(i)->getFlist().size(); j++) // 친구리스트에 있는 친구들의 친구리스트
		{
			if (loginedUser != loginedUser->getFlist().at(i)->getFlist().at(j)) // 다른 친구들의 친구에 포함된 "나"는 제외(예외처리)
			{
				RecommandList1.push_back(loginedUser->getFlist().at(i)->getFlist().at(j));
			}
		}
	}
	if (RecommandList1.size() == 0)
	{
		cout << "추천할 친구가 없습니다!" << endl;
		return;
	}

	for (int i = 0; i < RecommandList1.size(); i++)
	{
		cout << i + 1 << " ." << RecommandList1[i]->getattrs()["이름"];
		cout << " 나이 : " << RecommandList1[i]->getattrs()["나이"];
		cout << " 성별 : " << RecommandList1[i]->getattrs()["성별"];
		cout << " 학교 : " << RecommandList1[i]->getattrs()["학교"];
		cout << " 지역 : " << RecommandList1[i]->getattrs()["지역"] << endl;
	}
	cout << endl;
}

void App::friednType2()
// 자기자신은 안뜨게해야함 < 오류의 원인일듯
{
	vector<User*> RecommandList2; // 추천 방식(2)
	
	for (int i = 0; i < userList.size(); i++)
	{
		if (userList[i]->getId() == loginedUser->getId())
		{
			continue;
			// 만약 자기자신이면 건너뛰고 다음부터 포문돌려!
		}
		int flag = 0; // 속성값 일치 갯수 확인
		if (loginedUser->getattrs()["이름"] == userList.at(i)->getattrs()["이름"])
		{
			flag += 1;
		}
		if (loginedUser->getattrs()["나이"] == userList.at(i)->getattrs()["나이"])
		{
			flag += 1;
		}
		if (loginedUser->getattrs()["성별"] == userList.at(i)->getattrs()["성별"])
		{
			flag += 1;
		}
		if (loginedUser->getattrs()["학교"] == userList.at(i)->getattrs()["학교"])
		{
			flag += 1;
		}
		if (loginedUser->getattrs()["지역"] == userList.at(i)->getattrs()["지역"])
		{
			flag += 1;
		}
		if (flag >= 3)
		{
			RecommandList2.push_back(userList.at(i));
			// 공통점이 세개 이상인 친구는 벡터에 저장
		}
	}
	if (!RecommandList2.size())
	{
		cout << "추천할 친구가 없습니다!" << endl;
		return;
	}
	// 예외처리

	for (int i = 0; i < RecommandList2.size(); i++)
	{
		cout << "\n" << i + 1 << " ." << RecommandList2[i]->getattrs()["이름"] << endl;
		cout << "나이 : " << RecommandList2[i]->getattrs()["나이"] << endl;
		cout << "성별 : " << RecommandList2[i]->getattrs()["성별"] << endl;
		cout << "학교 : " << RecommandList2[i]->getattrs()["학교"] << endl;
		cout << "지역 : " << RecommandList2[i]->getattrs()["지역"] << endl;
	}
	cout << endl;
}
// 친구 추천 
// 속성 값이 3개 이상 동일한 사람들을 추천 받음
// 각각의 속성에 대하여 비교로직을 만든다.
// 비교후 같으면 true 다르면 false를 리턴
// true가 3개이상 나오면 추천!

void App::requestFriend()
{
	string name;
	cout << "친구 신청할 사람의 이름을 입력하세요 : ";
	cin >> name;
	vector<int> Id;
	int idx = 1;


	cout << "0. 뒤로가기" << endl;
	for (int i = 0; i < userList.size(); i++)
	{
		if (userList.at(i)->getattrs()["이름"] == name)
		{
			cout << idx++ << ". " << "이름 : " << userList.at(i)->getattrs()["이름"];
			cout << " 나이: " << userList.at(i)->getattrs()["나이"];
			cout << " 성별: " << userList.at(i)->getattrs()["성별"];
			cout << " 학교: " << userList.at(i)->getattrs()["학교"];
			cout << " 지역: " << userList.at(i)->getattrs()["지역"] << endl;
			Id.push_back(userList.at(i)->getId()); // 찾은 친구의 아이디를 저장 임시벡터
		}
		// 같은 이름을 가진 사람들 출력 (동명이인 가능)
	}
	if (Id.size() == 0)
	{
		cout << "일치하는 사용자가 없습니다!" << endl;
		return;
	}
	int num;
	cout << "친구 신청할 사람 선택 : ";
	cin >> num;
	if (num == 0)
	{
		return; // 뒤로가기
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
						cout << "이미 " << userList[i]->getattrs()["이름"] << "님과 친구입니다!" << endl;
						return;

					}

				}
				userList.at(i)->addRecievedFR(loginedUser);
				// 친추한 친구의 요청친구 벡터에 로그인한 사용자 저장
				cout << "친구추가 완료!" << endl;
			}
		}
	}
}

void App::acceptFriend()
{
	if (loginedUser->getrecievedFR().size() == 0)
	{
		cout << "받은 친구 목록이 없습니다!" << endl;
		return;
	}
	cout << "받은 친구 신청 목록" << endl;
	for (int i = 0; i < loginedUser->getrecievedFR().size(); i++)
	{
		cout << endl;
		cout << i + 1 << "	." << loginedUser->getrecievedFR()[i]->getattrs()["이름"] << endl;
		cout << "성별 : " << loginedUser->getrecievedFR()[i]->getattrs()["성별"] << endl;
		cout << "나이 : " << loginedUser->getrecievedFR()[i]->getattrs()["나이"] << endl;
		cout << "학교 : " << loginedUser->getrecievedFR()[i]->getattrs()["학교"] << endl;
		cout << "지역 : " << loginedUser->getrecievedFR()[i]->getattrs()["지역"] << endl;
	}

	int command = GetCommand(loginedUser->getrecievedFR().size());
	if (command == 0)
	{
		return; // 뒤로가기
	}
	else
	{
		command -= 1; // 선택할때 +1 해서 선택했으므로
		User* selecUser = new User;
		selecUser = loginedUser->getrecievedFR()[command];
		loginedUser->addFriend(selecUser);
		selecUser->addFriend(loginedUser);
		cout << "이제부터 " << loginedUser->getrecievedFR()[command]->getattrs()["이름"] << "님과 친구입니다!" << endl;
		loginedUser->EraseRecieved(command);
	}
}

void App::rejectFriend()
{
	if (loginedUser->getrecievedFR().size() == 0)
	{
		cout << "받은 친구 목록이 없습니다!" << endl;
		return;
	}
	cout << "받은 친구 신청 목록" << endl;
	for (int i = 0; i < loginedUser->getrecievedFR().size(); i++)
	{
		cout << endl;
		cout << i + 1 << "	." << loginedUser->getrecievedFR()[i]->getattrs()["이름"] << endl;
		cout << "성별 : " << loginedUser->getrecievedFR()[i]->getattrs()["성별"] << endl;
		cout << "나이 : " << loginedUser->getrecievedFR()[i]->getattrs()["나이"] << endl;
		cout << "학교 : " << loginedUser->getrecievedFR()[i]->getattrs()["학교"] << endl;
		cout << "지역 : " << loginedUser->getrecievedFR()[i]->getattrs()["지역"] << endl;
	}

	int command = GetCommand(loginedUser->getrecievedFR().size());
	if (command == 0)
	{
		return; // 뒤로가기
	}
	else
	{
		command -= 1; // 선택할때 +1 해서 선택했으므로
		User* selecUser = new User;
		selecUser = loginedUser->getrecievedFR()[command];
		cout << loginedUser->getrecievedFR()[command]->getattrs()["이름"] << "님의 친구요청을 삭제했습니다!" << endl;
		loginedUser->EraseRecieved(command);
	}
}

int App::GetCommand(int maxCommand)
{
	while (true)
	{
		int command;
		cout << "번호를 입력하세요 : ";
		cin >> command;

		if (cin.fail())
		{
			cout << "올바르지 않은 입력입니다." << endl;
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
				cout << "올바르지 않은 입력입니다." << endl;
			}
		}
	}
	cout << "▷───────────────────────────────◁" << endl;
}