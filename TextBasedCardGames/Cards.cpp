#include "Cards.h"
#include <string>
using namespace std;

Cards::Cards()
{
	this->CanStackWith;
	this->CardName;
}

void Cards::CardDefine(string Card, string Stack, int ID)
{
	this->CardName = Card;
	this->CanStackWith = Stack;
	this->CardID = ID;
}

void Cards::CardPrint()
{
	
}