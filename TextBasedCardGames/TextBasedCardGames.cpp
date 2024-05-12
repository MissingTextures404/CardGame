#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <numeric>
#include <time.h>
#include <Windows.h>
#include "FakeBank.h"
#include "Cards.h"
using namespace std;

//checks the string to find a word then returns true if it finds the word
//this is probably the most important function in my eyes since it allows for the player to just type what ever but if they use the right word it works
int FindWord(string word, string FindThisWord)
{
	transform(word.begin(), word.end(), word.begin(), toupper);
	int pos;
	for (int i = 1; (pos = word.find(FindThisWord)) != -1; i++)
	{
		word = word.substr(++pos);
		return true;
	}
	return false;
}
void BlackJack();
void Solitare();

int main()
{
	string User;
	FakeBank Bank = FakeBank();
	
	cout << "Choose a game, Blackjack or Solitare, or you can deposit or check bank" << endl;
	while (true)
	{
		getline(cin, User);
		if (FindWord(User, "BLACKJACK"))
		{
			BlackJack();
			break;
		}
		else if (FindWord(User, "SOLITARE"))
		{
			Solitare();
			break;
		}
		else if (FindWord(User, "BANK"))
		{
			cout << "You currently have " << Bank.ReturnBalance() << endl;
		}
		else if (FindWord(User, "QUIT"))
		{
			break;
		}
		else if (FindWord(User, "CLEAR"))
		{
			system("cls");
		}
		else
		{
			cout << "You cant do that" << endl;
		}
	}
}


//Game 1: Blackjack, the games are all placed under main since they can still be called because they are definded above main
//and they can still use FindWord(), also it makes it easier to read
void BlackJack()
{
	srand(time(NULL));
	system("cls");
	cout << "Welcome to BlackJack..." << endl;
	cout << "The goal of the game is to beat the dealer by having you cards add up closer to 21 than the dealers cards" << endl;
    string Userin;
	vector<int> DealerHand, DealerFaceDown;
	vector<int> PlayerHand;
	int card, DealerCardsValue, PlayerCardsValue;
	int DealerStopValue = 17;
	bool DealerSmarter = false;
	bool PlayerWentBust = false;
	bool DealerWentBust = false;

	cout << "Select a difficulty \n 1. Easy \n 2. Normal \n 3. Hard \n";
	while (true)
	{
		getline(cin, Userin);
		if (FindWord(Userin, "EASY") || FindWord(Userin, "1"))
		{
			DealerStopValue = 10;
			break;
		}
		else if (FindWord(Userin, "NORMAL") || FindWord(Userin, "2"))
		{
			DealerStopValue = 17;
			break;
		}
		else if (FindWord(Userin, "HARD") || FindWord(Userin, "3"))
		{
			DealerStopValue = 17;
			DealerSmarter = true;
			break;
		}
	}
	//gives the player their starting 2 cards and checks if its an ace to allow for the optional 1 or 11 value.
	for (int i = 0; i!=2; i++)
	{
		card = rand() % 10;
		while (card == 0)
		{
			card = rand() % 10;
		}
		if (card == 1)
		{
			cout << "You got an ace do you want it to be an 11 or a 1" << endl;
			getline(cin,Userin);
			if (FindWord(Userin, "11") || FindWord(Userin, "ELEVEN"))
			{
				PlayerHand.push_back(11);
			}
			else if (FindWord(Userin, "1") || FindWord(Userin, "ONE"))
			{
				PlayerHand.push_back(1);
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
			break;
		}
		getline(cin, Userin);

		if (FindWord(Userin, "CHECK"))
		{
			cout << "You currently have cards that add up to the value of " << PlayerCardsValue << endl;
		}
		
		if (FindWord(Userin, "HIT"))
		{
			card = rand() %10;
			while (card == 0)
			{
				card = rand() % 10;
			}
			if (card == 1)
			{
				cout << "You got an ace do you want it to be an 11 or a 1" << endl;
				getline(cin,Userin);
				if (FindWord(Userin, "11") || FindWord(Userin, "Eleven"))
				{
					PlayerHand.push_back(11);
				}
				else if (FindWord(Userin, "1") || FindWord(Userin, "One"))
				{
					PlayerHand.push_back(1);
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
		if (FindWord(Userin, "STAND") || FindWord(Userin, "NO MORE"))
		{
			break;
		}
    }
	//the "ai" for the blackjack game, intially started off standing at 12 and above but it didnt feel like it was taking enough risks as it never went bust
	//so now it will stop at 17 or above, making it more likely for them to go bust 
	while (true)
	{
		card = rand() % 11;
		if (DealerSmarter)
		{
			if (card == 1 || card == 11)
			{
				if (DealerCardsValue < 11)
				{
					card = 1;
				}
				else if (DealerCardsValue >= 11)
				{
					card = 11;
				}
			}
		}
		DealerHand.push_back(card);
		DealerCardsValue = accumulate(DealerHand.begin(), DealerHand.end(), 0);
		if (DealerCardsValue <= 11)
		{
			cout << "The Dealer takes another card" << endl;
		}
		else if (DealerCardsValue >= DealerStopValue && DealerCardsValue < 21)
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
			DealerWentBust = true;
			break;
		}
	}

	if (PlayerCardsValue == DealerCardsValue && !PlayerWentBust && !DealerWentBust)
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

	cout << "\n would you like to play again?\n";
	while (true)
	{
		getline(cin, Userin);
		if (FindWord(Userin, "YES") || FindWord(Userin, "Y"))
		{
			BlackJack();
		}
		else if (FindWord(Userin, "NO") || FindWord(Userin, "N"))
		{
			main();
		}
		else if (FindWord(Userin, "QUIT"))
		{
			break;
		}
	}
}

//Game 2: Solitare

void Solitare()
{
	system("cls");
	cout << "Welcome to Solitare" << endl;

	enum TheCards 
	{None, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, SJ, SK, SQ, 
	C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, CJ, CK, CQ, 
	H1, H2, H3, H4, H5, H6, H7, H8, H9, H10, HJ, HK, HQ, 
	D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, DJ, DK, DQ};
	
	// allows the Text to be coloured to help with identifying what colour the card is

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	cout << "i should be red";
	SetConsoleTextAttribute(hConsole, 7);
	cout << "i should be white again";
}
