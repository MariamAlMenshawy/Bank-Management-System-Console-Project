#pragma once
#include<iostream>
#include<vector>
#include"Client.h"
#include"Time.h"

using namespace std;
class BankAccount 
{
protected:
	string accountHolder;
	string accountNumber;
	string password;
	double accountBalance;
	vector<Time>transaction;

public:
	
	void set_accountHolder(Client& c) {
		accountHolder = c.FullName();
	}
	void set_accountNumber(Client& c) {
		accountNumber = c.AccountNumber();
	}

	void set_accountBalance(Client& c) {
		accountBalance = c.Balance();
	}
	void set_password(Client& c) {
		password = c.Password();
	}

	string AccountHolder() { return accountHolder; }
	string AccountNumber()  { return accountNumber; }
	double AccountBalance()  { return accountBalance; }
	string Password()  { return password; }
	
	
	double deposit(double balance, string cCurrency, double amount, string currency,string accNum);
	double Withdraw(double balance, string cCurrency, double amount, string currency, string accNum);
	pair<double, double> transfer(double balance, double otherbalance, double amount, string currency, string cCurrency, string OtherCurrency, string accNum);

	void checkBalance(string currency);	

};
