#include <iostream>
#include <string>
using namespace std;
#pragma once
class Card
{
public:
	Card();
	~Card();

	int getnumber();
	int getsuit();

	void setnumber(int num);
	void setsuit(int s);

	void printMyInformation();
private:
	int number; // 2~10, J=11,Q=12,K=13,A=14
	int suit; // 무늬 : 1~4 (스,다,클,하)
};