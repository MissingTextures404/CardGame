#pragma once
#include <string>
using namespace std;
class Cards
{
	string CardName, CardSuit;
	int CardID, CanStackWith, CardColour;

public: void CardDefine(string Card, int Stack, string Suit, int ID, int Colour);
};