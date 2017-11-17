#include "Card.h"



Card::Card()
{
}


Card::~Card()
{
}

int Card::getnumber()
{
	return number;
}

int Card::getsuit()
{
	return suit;
}

void Card::setnumber(int num)
{
	number = num;
}

void Card::setsuit(int s)
{
	suit = s;
}

enum SUIT {Spade=0,Dia,Clover,Heart};
void Card::printMyInformation()
{
	string character;
	switch (number)
	{
	case 2:
		character = "2";
		break;
	case 3:
		character = "3";
		break;
	case 4:
		character = "4";
		break;
	case 5:
		character = "5";
		break;
	case 6:
		character = "6";
		break;
	case 7:
		character = "7";
		break;
	case 8:
		character = "8";
		break;
	case 9:
		character = "9";
		break;
	case 10:
		character = "10";
		break;
	case 11:
		character = 'J';
		break;
	case 12:
		character = 'Q';
		break;
	case 13:
		character = 'K';
		break;
	case 14:
		character = 'A';
		break;
	}

	switch (suit)
	{
	case Spade:
		cout << character; 
		cout << "¢¼";
		break;
	case Dia:
		cout << character;
		cout << "¡ß";
		break;
	case Clover:
		cout << character;
		cout << "¢À";
		break;
	case Heart:
		cout << character;
		cout << "¢¾";
		break;
	}
}
