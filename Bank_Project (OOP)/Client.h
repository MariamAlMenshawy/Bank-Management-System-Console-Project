#pragma once
#include<iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

class Client 
{
protected:
	string clientID;
	string fullName;
	string nationalID;
	string phoneNumber;
	string email;
	string accountType;
	string accountNumber;
	string currency;
	double balance;
	string password;
	string date;

public:
	void set_FullName(string name) {
		fullName = name;
	}
	void set_AccountNumber(string num) {
		accountNumber = num;
	}

	void set_balance(double b) {
		this->balance = b;
	}
	void set_Password(string p) {
		password = p;
	}
	void set_data() {
		time_t now = time(0);
		tm localTime;
		localtime_s(&localTime, &now);
		stringstream ss;
		ss << put_time(&localTime, "%Y-%m-%d");
		date = ss.str();
	}
	Client (){ }
	string ClientId() { return clientID; }
	string FullName() { return fullName; }
	string NationalId() { return nationalID; }
	string PhoneNumber() { return phoneNumber; }
	string Email() { return email; }
	string AccountType() { return accountType; }
	string AccountNumber() { return accountNumber; }
	string Currency() { return currency; }
	double Balance() { return balance; }
	string Password() { return password; }
	string Date() { return date; }

	string convertDataToLine(Client& data, string sep = "||");
	Client convertLineToData(string& line, string sep = "||");

	int clientId();
	long long accountnum();

	void AddOrUpdate();
	bool Delete(string num);

	void clientList();
	void viewClientAccounts();
	void addNewClient();
	void createNewAccount();
	void deleteAccount();
	void updateAccountInfo();
	void findAccount();

	void manageClientsScreen();
	void choiceManageClientsMain(int n);
};