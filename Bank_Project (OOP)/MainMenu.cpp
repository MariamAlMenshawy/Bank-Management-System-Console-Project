#include"MainMenu.h"
#include"Users.h"
#include"Client.h"
#include"Transactions.h"
#include<iostream>
#include<Windows.h>
#include<cstdlib>
using namespace std;

void MainMenu :: mainScreen(bool first) {
	system("cls");

	if (first) {
		cout << " \n\n \t\t\t\t      Welcome To Bank System          ";
		first = false;
	}

	cout << "\n\t\t\t" << string(50, '_') << endl << endl;
	cout << "  \t\t\t\t  \t    Main Menu          \n";
	cout << "\t\t\t" << string(50, '_') << endl << endl;
	cout << "\t\t\t1. Manage Clients\n";
	cout << "\t\t\t2. Transactions\n";
	cout << "\t\t\t3. Manage Users\n";
	cout << "\t\t\t4. Exit Program\n";
	cout << "\t\t\t" << string(50, '_') << endl << endl;

	int num;
	do {
		cout << "\t\t\tEnter what do you want to do? [1 to 4] ";
		cin >> num;
	} while (num <= 0 || num > 4);

	choiceMainMenu(num);
}
void MainMenu:: choiceMainMenu(int n) {
	if (n == 1) {
		Client c;
		c.manageClientsScreen();
	}
	else if (n == 2) {
		Transactions t;
		t.manageTransactionScreen();
	}
	else if (n == 3) {
		Users u;
		u.manageUsersScreen();
	}
	else {
		cout << endl << endl;
		exit(0);
	}
}

