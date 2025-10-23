#include"BankAccount.h"
#include"Client.h"
#include<iostream>
#include<utility>
#include <iomanip>
#include <locale>
using namespace std;
 
double BankAccount ::deposit(double balance,string cCurrency,double amount,string currency,string accNum) {
	if (amount > 0) {
		if (currency == "EGP" && cCurrency == "EGP") {
			accountBalance = balance + amount;
		}
		else if (currency == "USD" && cCurrency == "EGP") {
			accountBalance = balance + (50*amount);
		}
		else if (currency == "USD" && cCurrency == "USD") {
			accountBalance = balance + amount;
		}
		else {
			accountBalance = balance + (amount/50);
		}
		transaction.push_back(Time("Deposit", amount, currency, accNum));
	}
	else {
		cout << "\t\t\tInvalid amount!\n";
	}
	return accountBalance;
}
double BankAccount :: Withdraw(double balance, string cCurrency, double amount, string currency,string accNum) {
	if (amount > balance) {
		cout << "\t\t\tSorry, You can't withdraw. Your balance is not enough!" << endl;
	}
	else if (amount <= 0) {
		cout << "\t\t\tInvalid amount!\n";
	}
	else {
		if (currency == "EGP" && cCurrency == "EGP") {
			accountBalance = balance - amount;
		}
		else if (currency == "USD" && cCurrency == "EGP") {
			accountBalance = balance - (50 * amount);
		}
		else if (currency == "USD" && cCurrency == "USD") {
			accountBalance = balance - amount;
		}
		else {
			accountBalance = balance - (amount / 50);
		}
		transaction.push_back(Time("Withdraw", amount, currency, accNum));
		
	}

	return accountBalance;
}

pair<double, double> BankAccount::transfer(double balance,double otherbalance,double amount,string currency,string cCurrency,string OtherCurrency,string accNum) {
	double newSenderBalance = Withdraw(balance, cCurrency, amount, currency,accNum);
	double newReceiverBalance = deposit(otherbalance, OtherCurrency, amount, currency,accNum);
	transaction.push_back(Time("Transfer", amount, currency, accNum));
	return { newSenderBalance, newReceiverBalance };
}

void BankAccount :: checkBalance(string currency) {
	cout << "\n\t\t\t================= Account Details ================= \n";
	cout << "\t\t\tThe Account Holder's Name: " << accountHolder << endl;
	cout << "\t\t\tThe Account Number: " << accountNumber << endl;
	cout << fixed << setprecision(2);
	cout.imbue(std::locale("en_US.UTF-8"));
	cout << "\t\t\tCurrent Balance: " << accountBalance<<" "<<currency;
	cout << "\n\t\t\t=================================================== \n";
}
