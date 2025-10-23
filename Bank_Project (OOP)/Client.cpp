#include"Client.h"
#include"MainMenu.h"
#include<iostream>
#include <sstream>
#include <iomanip>
#include<fstream>
#include<vector>
#include<Windows.h>
using namespace std;

string Client::convertDataToLine(Client &data, string sep) {
	return data.clientID + sep
		+ data.fullName + sep
		+ data.nationalID + sep
		+ data.phoneNumber + sep
		+ data.email + sep
		+ data.accountType + sep
		+ data.accountNumber + sep
		+ data.currency + sep
		+ to_string(data.balance) + sep
		+ data.password + sep
		+ data.date;
}

Client Client::convertLineToData(string &line, string sep ) {
	Client c;

	size_t pos1 = line.find(sep);
	size_t pos2 = line.find(sep, pos1 + sep.size());
	size_t pos3 = line.find(sep, pos2 + sep.size());
	size_t pos4 = line.find(sep, pos3 + sep.size());
	size_t pos5 = line.find(sep, pos4 + sep.size());
	size_t pos6 = line.find(sep, pos5 + sep.size());
	size_t pos7 = line.find(sep, pos6 + sep.size());
	size_t pos8 = line.find(sep, pos7 + sep.size());
	size_t pos9 = line.find(sep, pos8 + sep.size());
	size_t pos10 = line.find(sep, pos9 + sep.size());

	c.clientID = line.substr(0, pos1);
	c.fullName = line.substr(pos1 + sep.size(), pos2 - pos1 - sep.size());
	c.nationalID = line.substr(pos2 + sep.size(), pos3 - pos2 - sep.size());
	c.phoneNumber = line.substr(pos3 + sep.size(), pos4 - pos3 - sep.size());
	c.email = line.substr(pos4 + sep.size(), pos5 - pos4 - sep.size());
	c.accountType = line.substr(pos5 + sep.size(), pos6 - pos5 - sep.size());
	c.accountNumber = line.substr(pos6 + sep.size(), pos7 - pos6 - sep.size());
	c.currency = line.substr(pos7 + sep.size(), pos8 - pos7 - sep.size());
	string b = line.substr(pos8 + sep.size(), pos9 - pos8 - sep.size());
	c.balance = stod(b);
	c.password = line.substr(pos9 + sep.size(), pos10 - pos9 - sep.size());
	c.date = line.substr(pos10 + sep.size());

	return c;

}

int Client::clientId() {
	string line;
	int id = 1000;
	ifstream clients("Clients.txt");
	while (getline(clients, line)) {
		Client c= convertLineToData(line);
		if (stoi(c.clientID) >= id) {
			id = stoi(c.clientID);
		}
	}
	clients.close();
	id++;
	return id;
}

long long Client::accountnum() {
	string line;
	long long accNum = 100000;
	ifstream clients("Clients.txt");
	while (getline(clients, line)) {
		Client c = convertLineToData(line);
		if (stoll(c.accountNumber) >= accNum) {
			accNum = stoll(c.accountNumber);
		}
	}
	clients.close();
	accNum++;
	return accNum;
}

void Client::AddOrUpdate() {
	Client c;
	c.clientID = to_string(clientId());
	cout << "\t\t\tFull Name: ";
	getline(cin, c.fullName);
	cout << "\t\t\tNational Id: ";
	getline(cin, c.nationalID);
	cout << "\t\t\tPhone Number:  ";
	getline(cin, c.phoneNumber);
	cout << "\t\t\tEmail: ";
	getline(cin, c.email);
	cout << "\t\t\tAccount Type: \n";
	cout << "\t\t\t1. Current Account\n";
	cout << "\t\t\t2. Savings Account\n";
	int num;
	do {
		cout << "\t\t\tEnter 1 or 2 :";
		cin >> num;
		cin.ignore();
		if (num == 1) {
			c.accountType = "Current";
		}
		else {
			c.accountType = "Savings";
		}
	} while (num <= 0 || num > 2);
	c.accountNumber = to_string(accountnum());
	int numcurrency;
	cout << "\t\t\tCurrency: \n";
	cout << "\t\t\t1. EGP\n";
	cout << "\t\t\t2. USD\n";
	do {
		cout << "\t\t\tEnter 1 or 2: ";
		cin >> numcurrency;
		cin.ignore();
		if (numcurrency == 1) {
			c.currency = "EGP";
		}
		else {
			c.currency = "USD";
		}
	} while (numcurrency <= 0 || numcurrency > 2);
	cout << "\t\t\tBalance: ";
	cin >> c.balance;
	cin.ignore();
	cout << "\t\t\tPassword: ";
	getline(cin, c.password);
	c.set_data();
	ofstream clients("Clients.txt", ios::app);
	string line;
	line = convertDataToLine(c);
	clients << line << endl;
	clients.close();
}

bool Client::Delete(string num) {
	ifstream clients("Clients.txt");
	vector<Client>allClient;
	string line;
	bool found = false;
	while (getline(clients, line)) {
		Client c = convertLineToData(line);
		if (c.accountNumber != num) {
			allClient.push_back(c);
		}
		else {
			found = true;
		}
	}
	clients.close();

	ofstream clients2("Clients.txt");
	for (Client c : allClient) {
		clients2 << convertDataToLine(c) << endl;
	}
	clients2.close();

	return found;
}

void Client::clientList() {
	system("cls");
	cout << "\n\t\t\t" << string(50, '_') << endl << endl;
	cout << "\t\t\t                  Client List                   \n";
	cout << "\t\t\t" << string(50, '_') << endl << endl;
	
	
	cout << "\t" << string(85, '_') << endl << endl;

	string line;
	ifstream clients("Clients.txt");
	while (getline(clients, line)) {
		Client c = convertLineToData(line);
		
		cout << "\t\t\tClient Id: " << c.clientID << endl;
		cout << "\t\t\tFull Name: " << c.fullName << endl;
		cout << "\t\t\tNational Id: " << c.nationalID << endl;
		cout << "\t\t\tPhone Number: " << c.phoneNumber << endl;
		cout << "\t\t\tEmail: " << c.email << endl;
		cout << "\t\t\tAccount Type: " << c.accountType << endl;
		cout << "\t\t\tAccount Number: " << c.accountNumber << endl;
		cout << "\t\t\tBalance: " << c.balance <<" "<<c.currency<< endl;
		cout << "\t\t\tPassword: " << c.password << endl;
		cout << "\t\t\tOpen Date: " << c.date << endl << endl;
		cout << "\t\t\t====================================================\n";
		cout << endl;
	}
	cout << "\t" << string(85, '_') << endl << endl;

	clients.close();
}

void Client::viewClientAccounts() {
	system("cls");
	cout << "\n\t\t\t" << string(50, '_') << endl << endl;
	cout << "\t\t\t                View Client Accounts                  \n";
	cout << "\t\t\t" << string(50, '_') << endl << endl;

	cout << "\t\t\tEnter Client Id: ";
	string id;
	getline(cin, id);
	cout << "\t\t\tEnter Full Name: ";
	string fullname;
	getline(cin, fullname);
	cout << "\t\t\t" << string(50, '_') << endl ;
	cout << endl << endl;
	int count = 1;
	bool found = false;

	string line;
	ifstream clients("Clients.txt");
	while (getline(clients, line)) {
		Client c = convertLineToData(line);

		if (c.clientID == id && c.fullName == fullname) {
			found = true;
			cout << "\t\t\tAccount no." << count++<<": " << endl << endl;
			cout << "\t\t\tClient Id: " << c.clientID << endl;
			cout << "\t\t\tFull Name: " << c.fullName << endl;
			cout << "\t\t\tNational Id: " << c.nationalID << endl;
			cout << "\t\t\tPhone Number: " << c.phoneNumber << endl;
			cout << "\t\t\tEmail: " << c.email << endl;
			cout << "\t\t\tAccount Type: " << c.accountType << endl;
			cout << "\t\t\tAccount Number: " << c.accountNumber << endl;
			cout << "\t\t\tBalance: " << c.balance << " " << c.currency << endl;
			cout << "\t\t\tPassword: " << c.password << endl ;
			cout << "\t\t\tOpen Date: " << c.date << endl << endl;
			cout << "\t\t\t====================================================\n";
			cout << endl;
		}
		
	}
	if(!found){
		cout << "\n\n\t\t\t---------- Client not found! -----------\n";
		return;
	}
	clients.close();

}

void Client::addNewClient() {
	system("cls");
	cout << "\n\t\t\t" << string(50, '_') << endl << endl;
	cout << "\t\t\t                Add New Client                  \n";
	cout << "\t\t\t" << string(50, '_') << endl << endl;

	AddOrUpdate();

	cout << endl;
	cout << endl;
	cout << "\t\t\t---------- New client added successfully! -----------" << endl;
}

void Client::createNewAccount() {
	system("cls");
	cout << "\n\t\t\t" << string(50, '_') << endl << endl;
	cout << "\t\t\t                Create New Account                  \n";
	cout << "\t\t\t" << string(50, '_') << endl << endl;

	cout << "\t\t\tEnter Client Id: ";
	string id;
	getline(cin, id);
	cout << "\t\t\tEnter Full Name: ";
	string fullname;
	getline(cin, fullname);

	bool found = false;

	string nationalid;
	string line;
	ifstream clients("Clients.txt");
	while (getline(clients, line)) {
		Client c = convertLineToData(line);

		if (c.clientID == id && c.fullName == fullname) {
			nationalid = c.nationalID;
			found = true;
		}
	}
	clients.close();
	if (!found) {
		cout << "\n\n\t\t\t---------- Client not found! -----------\n";
		return;
	}
	Client c;
	c.clientID = id;
	c.fullName = fullname;
	c.nationalID = nationalid;
	cout << "\t\t\tPhone Number:  ";
	getline(cin, c.phoneNumber);
	cout << "\t\t\tEmail: ";
	getline(cin, c.email);
	cout << "\t\t\tAccount Type: \n";
	cout << "\t\t\t1. Current Account\n";
	cout << "\t\t\t2. Savings Account\n";
	int num;
	do {
		cout << "\t\t\tEnter 1 or 2 :";
		cin >> num;
		cin.ignore();
		if (num == 1) {
			c.accountType = "Current";
		}
		else {
			c.accountType = "Savings";
		}
	} while (num <= 0 || num > 2);
	c.accountNumber = to_string(accountnum());
	int numcurrency;
	cout << "\t\t\tCurrency: \n";
	cout << "\t\t\t1. EGP\n";
	cout << "\t\t\t2. USD\n";
	do {
		cout << "\t\t\tEnter 1 or 2: ";
		cin >> numcurrency;
		cin.ignore();
		if (numcurrency == 1) {
			c.currency = "EGP";
		}
		else {
			c.currency = "USD";
		}
	} while (numcurrency <= 0 || numcurrency > 2);
	cout << "\t\t\tBalance: ";
	cin >> c.balance;
	cin.ignore();
	cout << "\t\t\tPassword: ";
	getline(cin, c.password);
	c.set_data();
	ofstream clients2("Clients.txt", ios::app);
	string line2;
	line2 = convertDataToLine(c);
	clients2 << line2 << endl;
	clients.close();

	cout << endl;
	cout << endl;
	cout << "\t\t\t---------- The account has been created  -----------" << endl;

}

void Client::deleteAccount() {
	system("cls");
	cout << "\n\t\t\t" << string(50, '_') << endl << endl;
	cout << "\t\t\t                  Delete Account             \n";
	cout << "\t\t\t" << string(50, '_') << endl << endl;

	string num;
	cout << "\t\t\tEnter Account Number: ";
	getline(cin, num);

	char ans;
	cout << "\n\t\t\tAre you sure you want to delete this Account (y/n)? ";
	cin >> ans;
	cin.ignore();
	if (ans == 'y' || ans == 'Y') {

		bool found = Delete(num);

		if (found)
			cout << "\n\n\t\t\t---------- The account has been deleted successfully! -----------\n";
		else
			cout << "\n\n\t\t\t---------- Account not found! -----------\n";
	}
	else {
		cout << "\n\n\t\t\t---------- Operation was Cancelled -----------\n";
	}
		
}

void Client::updateAccountInfo() {
	system("cls");
	cout << "\n\t\t\t" << string(50, '_') << endl << endl;
	cout << "\t\t\t                  Update Account Info             \n";
	cout << "\t\t\t" << string(50, '_') << endl << endl;

	string num;
	cout << "\t\t\tEnter Account Number: ";
	getline(cin, num);

	char ans;
	cout << "\n\t\t\tAre you sure you want to update this account (y/n)? ";
	cin >> ans;
	cin.ignore();
	if (ans == 'y' || ans == 'Y') {

		bool found = Delete(num);

		if (!found) {
			cout << "\n\n\t\t\t---------- Account not found! -----------\n";
			return;
		}

	}
	else {
		cout << "\n\n\t\t\t---------- Operation was Cancelled -----------\n";
		return;
	}

	AddOrUpdate();

	cout << endl;
	cout << endl;
	cout << "\t\t\t---------- The account has been updated successfully! -----------" << endl;

}

void Client::findAccount() {
	system("cls");

	cout << "\n\t\t\t" << string(50, '_') << endl << endl;
	cout << "\t\t\t                  Find Account                   \n";
	cout << "\t\t\t" << string(50, '_') << endl << endl;

	string num;
	cout << "\t\t\tEnter Account Number:  ";
	getline(cin, num);

	bool found = Delete(num);

	if (!found) {
		cout << "\n\n\t\t\t---------- Account not found! -----------\n";
		return;
	}

	int number;
	cout << "\n\t\t\tWhat do you want to do? \n";
	cout << "\n\t\t\t1.Update account info ";
	cout << "\n\t\t\t2.Delete account ";
	cout << "\n\t\t\t--------------------------------------------------\n";
	do {
		cout << "\n\t\t\tEnter What do you want to do? [1 to 2] ";
		cin >> number;
		cin.ignore();
	} while (number <= 0 || number > 2);

	if (number == 2) {
		cout << "\n\n\t\t\t---------- The account has been deleted successfully! -----------\n";
	}
	else {

		AddOrUpdate();
		cout << endl;
		cout << endl;
		cout << "\t\t\t---------- The account has been updated successfully! -----------" << endl;

	}
}

void Client::manageClientsScreen() {
	system("cls");
	int num;
	cout << "\n\t\t\t--------------------------------------------------\n\n";
	cout << "  \t\t\t\t       Manage Clients Menu          \n\n";
	cout << "\t\t\t--------------------------------------------------\n\n";
	cout << "\t\t\t1. Show client list\n";
	cout << "\t\t\t2. View client Accounts\n";
	cout << "\t\t\t3. Add new client \n";
	cout << "\t\t\t4. Create new account \n";
	cout << "\t\t\t5. Delete account\n";
	cout << "\t\t\t6. Update account info\n";
	cout << "\t\t\t7. Find account\n";
	cout << "\t\t\t8. Main Menu\n";
	cout << "\n\t\t\t--------------------------------------------------\n";
	do {
		cout << "\n\t\t\tEnter What do you want to do? [1 to 8] ";
		cin >> num;
		cin.ignore();
	} while (num <= 0 || num > 8);
	choiceManageClientsMain(num);
}

void Client::choiceManageClientsMain(int n) {
	if (n == 1) {
		clientList();
	}
	else if (n == 2) {
		viewClientAccounts();
	}
	else if (n == 3) {
		addNewClient();
	}
	else if (n == 4) {
		createNewAccount();
	}
	else if (n == 5) {
		deleteAccount();
	}
	else if (n == 6) {
		updateAccountInfo();
	}
	else if (n == 7) {
		findAccount();
	}
	else {
		MainMenu menu;
		menu.mainScreen(false);
	}
	cout << "\n\t\t\tPress enter to return to the manage clients menu...\n";
	cin.get();
	manageClientsScreen();
}