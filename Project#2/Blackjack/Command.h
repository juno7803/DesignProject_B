#pragma once
#include "UserScoreInfo.h"
using namespace std;
class Command
{
public:
	Command();
	~Command();

	virtual void execute() = 0;
protected:
	string command_name;
};