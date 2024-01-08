#include <iostream>
#include <string>
#include "Blackjack.h"
#include "FakeBank.h"
using namespace std;

int FindWord(string word, string FindThisWord)
{
	int pos;
	//checks through the string the user puts into the game and then searches to find if that word is one of the words you want the player to use and then returns true or false
	for (int i = 1; (pos = word.find(FindThisWord)) != -1; i++)
	{
		word = word.substr(++pos);
		return true;
	}
	return false;
}

int main()
{
	string User;
	FakeBank Bank = FakeBank();
	
	cout << "Choose a game, Blackjack or Solitare, or you can deposit or check bank" << endl;
	while (true)
	{
		getline(cin, User);
		if (FindWord(User, "Blackjack"))
		{
			cout << "Blackjack it is" << endl;
		}
		if (FindWord(User, "Solitare"))
		{
			cout << "Solitare it is" << endl;
		}
		if (FindWord, "bank")
		{
			cout << "You currently have " << Bank.ReturnBalance() << endl;
		}
	}
}