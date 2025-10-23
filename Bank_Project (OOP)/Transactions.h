#pragma once
#include"Client.h"
#include"BankAccount.h"
#include<iostream>

using namespace std;

class Transactions
{
	double amount;
public:
	Client Find(string num);

	void displayDeposit();
	void displayWithdraw();
	void displayTransfer();

	double totalBalancesInEGP();
	void displayTotalBalances();

	void displayCheckBalance();
	Client FindSavings(string num);
	void displayInterest();

	void displayTransactionsHistory();
	void manageTransactionScreen();
	void choiceManageTransactionScreen(int n);
};
