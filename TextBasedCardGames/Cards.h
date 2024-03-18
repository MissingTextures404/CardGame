#pragma once
#include <string>
using namespace std;
class Cards
{
	string CardName, CanStackWith;
	int CardID;

	void CardDefine(string Card, string Stack, int ID);
	void CardPrint();
};

