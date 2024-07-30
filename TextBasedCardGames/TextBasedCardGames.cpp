#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <numeric>
#include <time.h>
#include <Windows.h>
#include <stack>
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
void PrintVector(vector<int> Vector);
void CardDef();

void Solitare()
{
	string Input;
	system("cls");
	cout << "Welcome to Solitare" << endl;

	vector<string> Cards =
	{
		"S1", "S2", "S3", "S4", "S5", "S6", "S7", "S8", "S9", "S10", "SJ", "SK", "SQ",
		"C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9", "C10", "CJ", "CK", "CQ",
		"H1", "H2", "H3", "H4", "H5", "H6", "H7", "H8", "H9", "H10", "HJ", "HK", "HQ",
		"D1", "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", "D10", "DJ", "DK", "DQ"
	};

	random_device rd;
	mt19937 g(rd());

	shuffle(Cards.begin(), Cards.end(), g);

	// allows the Text to be coloured to help with identifying what colour the card is, commented out text bellow is just a test

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	/*SetConsoleTextAttribute(hConsole, 12);
	cout << "i should be red";
	SetConsoleTextAttribute(hConsole, 7);
	cout << "i should be white again" << endl;*/
	int c = 0;
	while (true)
	{
		int b=0;
		for (string i : Cards)
		{
			//checks to see if they have gone through the deck twice
			if (c == 2)
			{
				SetConsoleTextAttribute(hConsole, 12);
				cout << "Game over" << endl;
				SetConsoleTextAttribute(hConsole, 7);
				break;
			}

			getline(cin, Input);
			cout << i << endl;
			// ten has to be at the top since FindWord doesnt discriminate
			if (FindWord(Input, "TEN") || (FindWord(Input, "10")))
			{
				if (i == "S10" || i == "C10" || i == "H10" || i == "D10")
				{
					Cards.erase(Cards.begin() + b);
					cout << " Card discarded" << endl;
					c = 0;
				}
			}
			else if (FindWord(Input, "ACE") || (FindWord(Input, "1"))
			){
				if (i == "S1" || i == "C1" || i == "H1" || i == "D1")
				{
					Cards.erase(Cards.begin()+b);
					cout << " Card discarded" << endl;
					c = 0;
				}
			}
			if (FindWord(Input, "TWO") || (FindWord(Input, "2"))
			){
				if (i == "S2" || i == "C2" || i == "H2" || i == "D2")
				{
					Cards.erase(Cards.begin() + b);
					cout << " Card discarded" << endl;
					c = 0;
				}
			}
			if (FindWord(Input, "THREE") || (FindWord(Input, "3")))
			{
				if (i == "S3" || i == "C3" || i == "H3" || i == "D3")
				{
					Cards.erase(Cards.begin() + b);
					cout << " Card discarded" << endl;
					c = 0;
				}
			}
			if (FindWord(Input, "FOUR") || (FindWord(Input, "4")))
			{
				if (i == "S4" || i == "C4" || i == "H4" || i == "D4")
				{
					Cards.erase(Cards.begin() + b);
					cout << " Card discarded" << endl;
					c = 0;
				}
			}
			if (FindWord(Input, "FIVE") || (FindWord(Input, "5")))
			{
				if (i == "S5" || i == "C5" || i == "H5" || i == "D5")
				{
					Cards.erase(Cards.begin() + b);
					cout << " Card discarded" << endl;
					c = 0;
				}
			}
			if (FindWord(Input, "SIX") || (FindWord(Input, "6")))
			{
				if (i == "S6" || i == "C6" || i == "H6" || i == "D6")
				{
					Cards.erase(Cards.begin() + b);
					cout << " Card discarded" << endl;
					c = 0;
				}
			}
			if (FindWord(Input, "SEVEN") || (FindWord(Input, "7")))
			{
				if (i == "S7" || i == "C7" || i == "H7" || i == "D7")
				{
					Cards.erase(Cards.begin() + b);
					cout << " Card discarded" << endl;
					c = 0;
				}
			}
			if (FindWord(Input, "EIGHT") || (FindWord(Input, "8")))
			{
				if (i == "S8" || i == "C8" || i == "H8" || i == "D8")
				{
					Cards.erase(Cards.begin() + b);
					cout << " Card discarded" << endl;
					c = 0;
				}
			}
			if (FindWord(Input, "NINE") || (FindWord(Input, "9")))
			{
				if (i == "S9" || i == "C9" || i == "H9" || i == "D9")
				{
					Cards.erase(Cards.begin() + b);
					cout << " Card discarded" << endl;
					c = 0;
				}
			}
			if (FindWord(Input, "KING"))
			{
				if (i == "SK" || i == "CK" || i == "HK" || i == "DK")
				{
					Cards.erase(Cards.begin() + b);
					cout << " Card discarded" << endl;
					c = 0;
				}
			}
			if (FindWord(Input, "QUEEN"))
			{
				if (i == "SQ" || i == "CQ" || i == "HQ" || i == "DQ")
				{
					Cards.erase(Cards.begin() + b);
					cout << " Card discarded" << endl;
					c = 0;
				}
			}
			if (FindWord(Input, "JACK"))
			{
				if (i == "SJ" || i == "CJ" || i == "HJ" || i == "DJ")
				{
					Cards.erase(Cards.begin() + b);
					cout << " Card discarded" << endl;
					c = 0;
				}
			}
			if (FindWord(Input, "PRINT ALL"))
			{
				cout << "DEBUG current full string :";
				for (string z : Cards)
				{
					cout << z << " ";
				}
				cout << endl;
			}
			b++;
		}
		c++;
	}
}
