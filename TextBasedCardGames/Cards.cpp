#include "Cards.h"
#include <string>
using namespace std;

Cards::Cards()
{
	this->CanStackWith;
	this->CardName;
}

void Cards::CardDefine(string Card, string Stack)
{
	this->CardName = Card;
	this->CanStackWith = Stack;
}

void Cards::CardPrint()
{
	
}