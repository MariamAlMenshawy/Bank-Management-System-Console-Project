#pragma once
#include"BankAccount.h"
#include"Client.h"
class SavingsAccount :public BankAccount 
{
	const double interestRate = 12;

public:
	int numberOfMonth(Client& c);
	double calculateMonthlyInterest(Client& c);
};
