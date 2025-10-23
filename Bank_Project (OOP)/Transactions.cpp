#include"Transactions.h"
#include"Client.h"
#include"MainMenu.h"
#include"Time.h"
#include"SavingsAccount.h"
#include<iostream>
#include<fstream>
#include<utility>
#include<iomanip>
#include<locale>
#include<Windows.h>

using namespace std;

Client Transactions::Find(string num) {
	ifstream clients("Clients.txt");
	vector<Client>allClient;
	string line;
	bool found = false;
	Client cl;
	while (getline(clients, line)) {
		Client c;
		c = c.convertLineToData(line);
		if (c.AccountNumber() != num) {
			allClient.push_back(c);
		}
		else {
			cl = c;
			found = true;
		}
	}
	if (!found) {
		Client emptyClient;
		return emptyClient;
	}
	clients.close();

	ofstream clients2("Clients.txt");
	for (Client c : allClient) {
		clients2 << c.convertDataToLine(c) << endl;
	}
	clients2.close();

	return cl;
}

void Transactions::displayDeposit() {
	system("cls");
	cout << "\n\t\t\t" << string(50, '_') << endl << endl;
	cout << "\t\t\t                  Deposit                   \n";
	cout << "\t\t\t" << string(50, '_') << endl << endl;
	
	string num;
	cout << "\t\t\tEnter Account Number:  ";
	getline(cin, num); 

	Client c = Find(num);
	if (c.AccountNumber().empty()) {
		cout << "\n\t\t\tOperation cancelled: Account not found.\n";
		return; 
	}
	BankAccount b;
	int numcurrency;
	string currency;
	cout << "\t\t\tAmount Currency: \n";
	cout << "\t\t\t1. EGP\n";
	cout << "\t\t\t2. USD\n";
	do {
		cout << "\t\t\tEnter 1 or 2 :";
		cin >> numcurrency;
		cin.ignore();
		if (numcurrency == 1) {
			currency="EGP";
		}
		else {
			currency = "USD";
		}
	} while (numcurrency <= 0 || numcurrency > 2);
	cout << "\t\t\tEnter Amount: ";
	double amount;
	cin >> amount;
	cin.ignore();
	cout << fixed << setprecision(2);
	cout.imbue(std::locale("en_US.UTF-8"));
	cout << "\n\t\t\tAccount balance before deposit: " << c.Balance() << " " << c.Currency() << endl;
	double newbalance = b.deposit(c.Balance(),c.Currency(), amount, currency,num);
	c.set_balance(newbalance);

	ofstream clients3("Clients.txt", ios::app);
	string line;
	line = c.convertDataToLine(c);
	clients3 << line << endl;
	clients3.close();
	cout << fixed << setprecision(2);
	cout.imbue(std::locale("en_US.UTF-8"));
	cout << "\n\t\t\tAccount balance after deposit "<< amount<<" "<<currency << " : " << c.Balance() << " " << c.Currency() << endl;

	cout << "\n\n\t\t\t---------- Deposit Successful! -----------\n";

}

void Transactions::displayWithdraw() {
	system("cls");
	cout << "\n\t\t\t" << string(50, '_') << endl << endl;
	cout << "\t\t\t                   Withdraw                   \n";
	cout << "\t\t\t" << string(50, '_') << endl << endl;

	string num;
	cout << "\t\t\tEnter Account Number:  ";
	getline(cin, num);

	Client c = Find(num);
	if (c.AccountNumber().empty()) {
		cout << "\n\t\t\tOperation cancelled: Account not found.\n";
		return;
	}
	BankAccount b;
	int numcurrency;
	string currency;
	cout << "\t\t\tAmount Currency: \n";
	cout << "\t\t\t1. EGP\n";
	cout << "\t\t\t2. USD\n";
	do {
		cout << "\t\t\tEnter 1 or 2: ";
		cin >> numcurrency;
		cin.ignore();
		if (numcurrency == 1) {
			currency = "EGP";
		}
		else {
			currency = "USD";
		}
	} while (numcurrency <= 0 || numcurrency > 2);
	cout << "\t\t\tEnter Amount: ";
	double amount;
	cin >> amount;
	cin.ignore();
	cout << fixed << setprecision(2);
	cout.imbue(std::locale("en_US.UTF-8"));
	cout << "\n\t\t\tAccount balance before withdraw: " << c.Balance() << " " << c.Currency() << endl;
	double newbalance = b.Withdraw(c.Balance(), c.Currency(), amount, currency,num);
	c.set_balance(newbalance);

	ofstream clients3("Clients.txt", ios::app);
	string line;
	line = c.convertDataToLine(c);
	clients3 << line << endl;
	clients3.close();
	cout << fixed << setprecision(2);
	cout.imbue(std::locale("en_US.UTF-8"));
	cout << "\n\t\t\tAccount balance after withdraw " << amount << " " << currency << " : " << c.Balance() << " " << c.Currency() << endl;

	cout << "\n\n\t\t\t---------- Withdraw Successful! -----------\n";

}

void Transactions::displayTransfer() {
	system("cls");
	cout << "\n\t\t\t" << string(50, '_') << endl << endl;
	cout << "\t\t\t                   Transfer                   \n";
	cout << "\t\t\t" << string(50, '_') << endl << endl;

	string num;
	cout << "\t\t\tEnter your account number:  ";
	getline(cin, num);

	Client c = Find(num);
	if (c.AccountNumber().empty()) {
		cout << "\n\t\t\tOperation cancelled: Account not found.\n";
		return;
	}

	string othernum;
	cout << "\t\t\tEnter the account number you want to transfer to: ";
	getline(cin, othernum);

	Client cl = Find(othernum);
	if (cl.AccountNumber().empty()) {
		cout << "\n\t\t\tOperation cancelled: Account not found.\n";
		return;
	}

	BankAccount b;
	int numcurrency;
	string currency;
	cout << "\t\t\tAmount Currency: \n";
	cout << "\t\t\t1. EGP\n";
	cout << "\t\t\t2. USD\n";
	do {
		cout << "\t\t\tEnter 1 or 2: ";
		cin >> numcurrency;
		cin.ignore();
		if (numcurrency == 1) {
			currency = "EGP";
		}
		else {
			currency = "USD";
		}
	} while (numcurrency <= 0 || numcurrency > 2);
	cout << "\t\t\tEnter Amount: ";
	double amount;
	cin >> amount;
	cin.ignore();
	cout << fixed << setprecision(2);
	cout.imbue(std::locale("en_US.UTF-8"));
	cout << "\n\t\t\tYour account balance before transfer: " << c.Balance() << " " << c.Currency() << endl;
	pair<double, double> newbalance = b.transfer(c.Balance(), cl.Balance(), amount, currency, c.Currency(), cl.Currency(),num);
	c.set_balance(newbalance.first);
	cl.set_balance(newbalance.second);

	ofstream clients3("Clients.txt", ios::app);
	string line,line2;
	line = c.convertDataToLine(c);
	line2 = cl.convertDataToLine(cl);
	clients3 << line << endl;
	clients3 << line2 << endl;
	clients3.close();
	cout << fixed << setprecision(2);
	cout.imbue(std::locale("en_US.UTF-8"));
	cout << "\n\t\t\tYour account balance after transfer " << amount << " " << currency << " : " << c.Balance() << " " << c.Currency() << endl;

	cout << "\n\n\t\t\t---------- Transfer Successful! -----------\n";

}

double Transactions::totalBalancesInEGP() {
	ifstream clients("Clients.txt");
	string line;
	double total = 0;
	while (getline(clients, line)) {
		Client c;
		c = c.convertLineToData(line);
		if (c.Currency() == "USD") {
			total += (c.Balance() * 50);
		}
		else {
			total += c.Balance();
		}
	}
	clients.close();
	return total;
}

void Transactions::displayTotalBalances() {
	system("cls");
	cout << "\n\t\t\t" << string(50, '_') << endl << endl;
	cout << "\t\t\t                Total Balances                  \n";
	cout << "\t\t\t" << string(50, '_') << endl << endl;

	int numcurrency;
	string currency;
	cout << "\t\t\tCurrency you want to display the total balance: \n";
	cout << "\t\t\t1. EGP\n";
	cout << "\t\t\t2. USD\n";
	double total = totalBalancesInEGP();
	do {
		cout << "\t\t\tEnter 1 or 2: ";
		cin >> numcurrency;
		cin.ignore();
		if (numcurrency == 1) {
			currency = "EGP";
		}
		else {
			total /= 50;
			currency = "USD";
		}
	} while (numcurrency <= 0 || numcurrency > 2);

	cout << fixed << setprecision(2);
	cout.imbue(std::locale("en_US.UTF-8"));
	cout << "\n\n\t\t\tTotal Balances: " << total << " " << currency << endl;
}

void Transactions::displayCheckBalance() {

	system("cls");
	cout << "\n\t\t\t" << string(50, '_') << endl << endl;
	cout << "\t\t\t                Check The Balance                  \n";
	cout << "\t\t\t" << string(50, '_') << endl << endl;

	string num;
	cout << "\t\t\tEnter Account Number: ";
	getline(cin, num);
	string currency;

	ifstream clients("Clients.txt");
	string line;
	while (getline(clients, line)) {
		Client c;
		c = c.convertLineToData(line);
		if (c.AccountNumber() == num) {
			BankAccount b;
			currency = c.Currency();

			b.set_accountHolder(c);
			b.set_accountNumber(c);
			b.set_accountBalance(c);

			b.checkBalance(currency);
			break;
		}
	}
}

Client Transactions::FindSavings(string num) {
	ifstream clients("Clients.txt");
	vector<Client>allClient;
	string line;
	bool found = false;
	Client cl;
	while (getline(clients, line)) {
		Client c;
		c = c.convertLineToData(line);
		if (c.AccountNumber() != num) {
			allClient.push_back(c);
		}
		else {
			cl = c;
			found = true;
		}
	}
	if (!found) {
		Client emptyClient;
		return emptyClient;
	}
	clients.close();

	ofstream clients2("Clients.txt");
	for (Client c : allClient) {
		clients2 << c.convertDataToLine(c) << endl;
	}
	clients2.close();

	return cl;
}

void Transactions::displayInterest() {
	system("cls");
	cout << "\n\t\t\t" << string(50, '_') << endl << endl;
	cout << "\t\t\t              Calculate Interest                  \n";
	cout << "\t\t\t" << string(50, '_') << endl << endl;

	string num;
	cout << "\t\t\tEnter Account Number: ";
	getline(cin, num);

	Client c = Find(num);
	if (c.AccountNumber().empty()) {
		cout << "\n\t\t\tOperation cancelled: Account not found.\n";
		return;
	}

	if (c.AccountType() == "Savings") {
	    cout << fixed << setprecision(2);
		cout.imbue(std::locale("en_US.UTF-8"));
		cout << "\n\t\t\tAccount balance before interest: " << c.Balance() << " " << c.Currency() << endl;
		SavingsAccount s;
		s.numberOfMonth(c);
		double new_balance = s.calculateMonthlyInterest(c);
		c.set_balance(new_balance);
		cout << fixed << setprecision(2);
		cout.imbue(std::locale("en_US.UTF-8"));
		cout << "\n\t\t\tAccount balance after interest: " << c.Balance() << " " << c.Currency() << endl;
	}
    else {
        cout << "\n\t\t\tThis account is current account. \n";
		return;
	}
	ofstream clients3("Clients.txt", ios::app);
	string line;
	line = c.convertDataToLine(c);
	clients3 << line << endl;
	clients3.close();
	
}

void Transactions::displayTransactionsHistory() {
	system("cls");
	cout << "\n\t\t\t" << string(50, '_') << endl << endl;
	cout << "\t\t\t               Transactions History                  \n";
	cout << "\t\t\t" << string(50, '_') << endl << endl;
    
	string num;
	cout << "\t\t\tEnter Account Number: ";
	getline(cin, num);

	cout << endl<<endl;
	cout << "\t\t" << left;
	cout << setw(5) << "#";
	cout << setw(20) << "Transaction Type";
	cout << setw(20) << "Amount";
	cout << setw(15) << "Currency";
	cout << setw(20) << "Time & Date";
	
	cout << endl;
	cout << "\t\t" << string(80, '_') << endl << endl;
	bool found = false;
	int id = 1;
	
	ifstream transactions("Transactions.txt");
	string line;
	while (getline(transactions, line)) {
		Time t;
		t = t.convertLineToData(line);
		if (t.AccountNumber() == num) {
			cout << "\t\t" << left;
			cout << setw(5) << id++;
			cout << setw(20) << t.Type();
			cout << setw(20) << t.Amount();
			cout << fixed << setprecision(2);
			cout.imbue(std::locale("en_US.UTF-8"));
			cout << setw(15) << t.Currency();
			cout << setw(20) << t.Date();
			cout << endl;
			found = true;
		}
	}
	if (!found) {
		cout << "\n\t\t\tAccount not found or transaction not found\n";
	}
	transactions.close();
	cout << "\n\t\t" << string(80, '_') << endl << endl;
}

void Transactions::manageTransactionScreen() {
	system("cls");
	int num;
	cout << "\n\t\t\t--------------------------------------------------\n\n";
	cout << "  \t\t\t\t       Transactions Menu          \n\n";
	cout << "\t\t\t--------------------------------------------------\n\n";
	cout << "\t\t\t1. Deposit \n";
	cout << "\t\t\t2. Withdraw \n";
	cout << "\t\t\t3. Transfer\n";
	cout << "\t\t\t4. Total balances\n";
	cout << "\t\t\t5. Check the balance\n";
	cout << "\t\t\t6. Calculate interest for savings account\n";
	cout << "\t\t\t7. Transactions history\n";
	cout << "\t\t\t8. Main Menu\n";
	cout << "\n\t\t\t--------------------------------------------------\n";
	do {
		cout << "\n\t\t\tEnter What do you want to do? [1 to 8] ";
		cin >> num;
		cin.ignore();
	} while (num <= 0 || num > 8);
	choiceManageTransactionScreen(num);
}

void Transactions::choiceManageTransactionScreen(int n) {
	if (n == 1) {
		displayDeposit();
	}
	else if (n == 2) {
		displayWithdraw();
	}
	else if (n == 3) {
		displayTransfer();
	}
	else if (n == 4) {
		displayTotalBalances();
	}
	else if (n == 5) {
		displayCheckBalance();
	}
	else if (n == 6) {
		displayInterest();
	}
	else if (n == 7) {
		displayTransactionsHistory();
	}
	else {
		MainMenu menu;
		menu.mainScreen(false);
	}
	cout << "\n\t\t\tPress enter to return to the transactions menu...\n";
	cin.get();
	manageTransactionScreen();
}