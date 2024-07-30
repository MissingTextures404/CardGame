#include "FakeBank.h"
#include <string>
using namespace std;

FakeBank::FakeBank()
{
	this->CurrBalance = 200;
	this->MoneyInHand = 0;
}


void FakeBank::deposit(float amout)
{
	CurrBalance += amout;
}


string FakeBank::ReturnBalance()
{
	string stbal;
	stbal = to_string(CurrBalance);
	return stbal;
}