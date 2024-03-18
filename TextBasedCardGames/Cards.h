#pragma once
#include <string>
using namespace std;
class Cards
{
	string CardName, CanStackWith;

	void CardDefine(string Card, string Stack);
	void CardPrint();
};

