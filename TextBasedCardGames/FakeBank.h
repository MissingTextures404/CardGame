#pragma once
#include <string>
using namespace std;
class FakeBank
{
public:
	float CurrBalance;
	float OverDraftLimit;
	float MoneyInHand;
	
	FakeBank();

	void deposit(float amout);
	void MoreHandMoney(float amout);
	string CheckHand();
	string ReturnBalance();
};

