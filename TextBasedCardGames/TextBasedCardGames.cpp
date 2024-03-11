#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <numeric>
#include "FakeBank.h"
using namespace std;

//checks the string to find a word then returns true if it finds the word
//this is probably the most important function in my eyes since it allows for the player to just type what ever but if they use the right word it works
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
void BlackJack();

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
			BlackJack();
			break;
		}
		else if (FindWord(User, "Solitare"))
		{
			cout << "Solitare it is" << endl;
		}
		else if (FindWord(User, "bank"))
		{
			cout << "You currently have " << Bank.ReturnBalance() << endl;
		}
		else
		{
			cout << "You cant do that" << endl;
		}
	}
}


//Game 1: Blackjack, the games are all placed under main since they can still be called and each game is still able to use FindWord()
void BlackJack()
{
	cout << "Welcome to BlackJack..." << endl;
	cout << "The goal of the game is to beat the dealer by having you cards add up closer to 21 than the dealers cards" << endl;
    string Userin;
	vector<int> DealerHand, DealerFaceDown;
	vector<int> PlayerHand;
	int card, DealerCardsValue, PlayerCardsValue;
	bool PlayerWentBust = false;
	bool DealerWentBust = false;
	//gives the player their starting 2 cards and checks if its an ace to allow for the optional 1 or 11 value.
	for (int i = 0; i!=1; i++)
	{
		card = rand() % 10;
		if (card == 1)
		{
			cout << "You got an ace do you want it to be an 11 or a 1" << endl;
			getline(cin,Userin);
			if (FindWord(Userin, "1") || FindWord(Userin, "One"))
			{
				PlayerHand.push_back(1);
			}
			else if (FindWord(Userin, "11") || FindWord(Userin, "Eleven"))
			{
				PlayerHand.push_back(11);
			}
		}
		else if (card == 10)
		{
			cout << "You got a picture card with a value of 10" << endl;
			PlayerHand.push_back(10);
		}
		else
		{
			cout << "You got a card with a value of " << card << endl;
			PlayerHand.push_back(card);
		}
	}

    while (true)
    {
		PlayerCardsValue = accumulate(PlayerHand.begin(), PlayerHand.end(), 0);
		if (PlayerCardsValue > 21)
		{
			cout << "You have gone bust" << endl;
			PlayerWentBust = true;
		}
		getline(cin, Userin);

		if (FindWord(Userin, "Check"))
		{
			cout << "You currently have cards that add up to the value of " << PlayerCardsValue << endl;
		}
		
		if (FindWord(Userin, "Hit"))
		{
			card = rand() %10;
			if (card == 1)
			{
				cout << "You got an ace do you want it to be an 11 or a 1" << endl;
				getline(cin,Userin);
				if (FindWord(Userin, "1") || FindWord(Userin, "One"))
				{
					PlayerHand.push_back(1);
				}
				else if (FindWord(Userin, "11") || FindWord(Userin, "Eleven"))
				{
					PlayerHand.push_back(11);
				}
			}
			else if (card == 10)
			{
				cout << "You got a picture card with the value of 10" << endl;
				PlayerHand.push_back(10);
			}
			else
			{
				cout << "You got a card with the value of " << card <<endl;
				PlayerHand.push_back(card);
			}
		}
		if (FindWord(Userin, "Stand") || FindWord(Userin, "No more"))
		{
			break;
		}
    }
	//the "ai" for the blackjack game
	while (true)
	{
		card = rand() % 11;
		DealerHand.push_back(card);
		DealerCardsValue = accumulate(DealerHand.begin(), DealerHand.end(), 0);
		if (DealerCardsValue <= 11)
		{
			cout << "The Dealer takes another card" << endl;
		}
		else if (DealerCardsValue >= 11 && DealerCardsValue < 21)
		{
			cout << "The Dealer ends with the vaule of " << DealerCardsValue << endl;
			break;
		}
		else if (DealerCardsValue == 21)
		{
			cout << "The Dealer ends with the perfect value of 21" << endl;
			break;
		}
		else if (DealerCardsValue > 21)
		{
			cout << "The Dealers hand is a bust" << endl;
			break;
		}
	}

	if (PlayerCardsValue = DealerCardsValue && !PlayerWentBust && !DealerWentBust)
	{
		cout << "You and the Dealer got the same amount, it is a Draw";
	}
	else if (PlayerCardsValue > DealerCardsValue && !PlayerWentBust && !DealerWentBust)
	{
		cout << "Your cards are higher than the dealers cards\n" << "You Win";
	}
	else if (PlayerCardsValue < DealerCardsValue && !PlayerWentBust && !DealerWentBust)
	{
		cout << "Your cards are lower than the dealers cards\n" << "You Lose";
	}
	else if (PlayerWentBust && !DealerWentBust)
	{
		cout << "Since you went bust, You Lose";
	}
	else if (PlayerWentBust && DealerWentBust)
	{
		cout << "Both you and the dealer went bust... \n" << "You both Lose";
	}
	else if (!PlayerWentBust && DealerWentBust)
	{
		cout << "Since the dealer went bust\n" << "You Win";
	}
}