#include <iostream>
#include <string>
#include "FakeBank.h"
using namespace std;

//checks the string to find a word then returns true if it finds the word
int FindWord(string word, string FindThisWord)
{
	int pos;
	for (int i = 1; (pos = word.find(FindThisWord)) != -1; i++)
	{
		word = word.substr(++pos);
		return true;
		//debug inorder to test the Recognised words
		cout << "Recognised word " << FindThisWord << endl;
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
			BlackJack();
			break;
		}
		if (FindWord(User, "Solitare"))
		{
			cout << "Solitare it is" << endl;
		}
		if (FindWord(User, "bank"))
		{
			cout << "You currently have " << Bank.ReturnBalance() << endl;
		}
	}
}

void BlackJack()
{
	cout << "Welcome to BlackJack..." << endl;
    string Userin;
    while (true)
    {
        getline(cin, Userin);

		if (FindWord(Userin, "Hit"))
		{

		}
		if (FindWord(Userin, "Stand"))
		{
			
		}
    }
}