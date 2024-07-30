#include "Cards.h"
#include <string>
using namespace std;

Cards::Cards()
{
	this->CanStackWith;
	this->CardName;
}

void Cards::CardDefine(string Card, int Stack, string Suit, int ID, int Colour)
{
	this->CardName = Card;
	this->CanStackWith = Stack;
	this->CardSuit = Suit;
	this->CardID = ID;
	this->CardColour = Colour;
}