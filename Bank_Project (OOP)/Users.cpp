#include"Users.h"
#include"MainMenu.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<Windows.h>
#include <sstream>
#include <iomanip>
#include<vector>

using namespace std;

string Users::convertDataToLine(Users &data, string sep ) {
	return data.fullName + sep +
		   data.email + sep +
		   data.username + sep +
		   data.password;
}

Users Users::convertLineToData(string& line, string sep ) {
	Users user;

	size_t pos1 = line.find(sep);
	size_t pos2 = line.find(sep, pos1 + sep.size());
	size_t pos3 = line.find(sep, pos2 + sep.size());

	user.fullName = line.substr(0, pos1);
	user.email = line.substr(pos1 + sep.size(), pos2 - pos1 - sep.size());
	user.username = line.substr(pos2 + sep.size(), pos3 - pos2 - sep.size());
	user.password = line.substr(pos3 + sep.size());

	return user;
}

void Users::userList() {
	system("cls");
	cout << "\n\t\t\t" << string(50, '_') << endl << endl;
	cout << "\t\t\t                  User List                   \n";
	cout << "\t\t\t" << string(50, '_') << endl << endl;
	cout << "\t"<<left;
	cout << setw(5) << "#";
	cout << setw(25) << "Full Name";
	cout << setw(25) << "Email";
	cout << setw(15) << "Username";
	cout << setw(15) << "Password";
	cout << endl;
	cout << "\t" << string(85, '_') << endl << endl;
	int c=1;
	string line;
	ifstream users("Users.txt");
	while (getline(users, line)) {
		Users u = convertLineToData(line);
		cout << "\t"<<left;
		cout << setw(5) << c++;
		cout << setw(25) << u.fullName;
		cout << setw(25) << u.email;
		cout << setw(15) << u.username;
		cout << setw(15) << u.password;
		cout << endl;
	}
	cout << "\t" << string(85, '_') << endl << endl;
	
	users.close();
}

void Users::AddOrUpdate(){
	Users u;
	cout << "\t\t\tFull Name: ";
	getline(cin, u.fullName);
	cout << "\t\t\tEmail: ";
	getline(cin, u.email);
	cout << "\t\t\tUsername: ";
	getline(cin, u.username);
	cout << "\t\t\tPassword: ";
	getline(cin, u.password);

	string line;
	ofstream users("Users.txt", ios::app);
	line = convertDataToLine(u);
	users << line << endl;
	users.close();
}

bool Users::Delete(string name) {

	ifstream users("Users.txt");
	vector<Users> allUsers;
	string line;
	bool found = false;

	while (getline(users, line)) {
		Users u = convertLineToData(line);
		if (u.FullName() != name) {
			allUsers.push_back(u);
		}
		else {
			found = true;
		}
	}
	users.close();

	ofstream users2("Users.txt");
	for (Users u : allUsers) {
		users2 << convertDataToLine(u) << endl;
	}
	users2.close();

	return found;
}

void Users::addNewUser() {
	system("cls");
	cout<<"\n\t\t\t" << string(50, '_') << endl << endl;
	cout << "\t\t\t                  Add New User                   \n";
	cout << "\t\t\t" << string(50, '_') << endl << endl;

	AddOrUpdate();

	cout << endl;
	cout << endl;
	cout << "\t\t\t---------- New user added successfully! -----------" << endl;
	
}

void Users::deleteUser() {
	system("cls");
	cout << "\n\t\t\t" << string(50, '_') << endl << endl;
	cout << "\t\t\t                  Delete User                   \n";
	cout << "\t\t\t" << string(50, '_') << endl << endl;

	string name;
	cout << "\t\t\tEnter Full Name: ";
	getline(cin, name);

	char ans;
	cout << "\n\t\t\tAre you sure you want to delete this User (y/n)? ";
	cin >> ans;
	cin.ignore();
	if (ans == 'y' || ans == 'Y') {

		bool found = Delete(name);

		if (found)
			cout << "\n\n\t\t\t---------- User deleted successfully! -----------\n";
		else
			cout << "\n\n\t\t\t---------- User not found! -----------\n";
	}
	else {
		cout << "\n\n\t\t\t---------- Operation was Cancelled -----------\n";
	}
}

void Users::updateUser() {
	system("cls");
	cout << "\n\t\t\t" << string(50, '_') << endl << endl;
	cout << "\t\t\t                  Update User Info                   \n";
	cout << "\t\t\t" << string(50, '_') << endl << endl;

	string name;
	cout << "\t\t\tEnter Full Name: ";
	getline(cin, name);

	char ans;
	cout << "\n\t\t\tAre you sure you want to update this User (y/n)? ";
	cin >> ans;
	cin.ignore();
	if (ans == 'y' || ans == 'Y') {

		bool found = Delete(name);

		if (!found) {
			cout << "\n\n\t\t\t---------- User not found! -----------\n";
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
	cout << "\t\t\t---------- User updated info successfully! -----------" << endl;

}

void Users::findUser() {
	system("cls");

	cout << "\n\t\t\t" << string(50, '_') << endl << endl;
	cout << "\t\t\t                  Find User                   \n";
	cout << "\t\t\t" << string(50, '_') << endl << endl;

	string name;
	cout << "\t\t\tEnter Full Name: ";
	getline(cin, name);

	bool found = Delete(name);

	if (!found) {
		cout << "\n\n\t\t\t---------- User not found! -----------\n";
		return;
	}

	int num;
	cout << "\n\t\t\tWhat do you want to do? \n";
	cout << "\n\t\t\t1.Update user info ";
	cout << "\n\t\t\t2.Delete user ";
	cout << "\n\t\t\t--------------------------------------------------\n";
	do {
		cout << "\n\t\t\tEnter What do you want to do? [1 to 2] ";
		cin >> num;
		cin.ignore();
	} while (num <= 0 || num > 2);
	
	if (num == 2) {
		cout << "\n\n\t\t\t---------- User deleted successfully! -----------\n";
	}
	else {
		
		AddOrUpdate();
		cout << endl;
		cout << endl;
		cout << "\t\t\t---------- User updated info successfully! -----------" << endl;
		
	}
}

void Users::manageUsersScreen() {
	system("cls");
	int num;
	cout << "\n\t\t\t--------------------------------------------------\n\n";
	cout << "  \t\t\t\t       Manage Users Menu          \n\n";
	cout << "\t\t\t--------------------------------------------------\n\n";
	cout << "\t\t\t1. Show user list\n";
	cout << "\t\t\t2. Add new user\n";
	cout << "\t\t\t3. Delete user\n";
	cout << "\t\t\t4. Update user info\n";
	cout << "\t\t\t5. Find user\n";
	cout << "\t\t\t6. Main Menu\n";
	cout << "\n\t\t\t--------------------------------------------------\n";
	do {
		cout << "\n\t\t\tEnter What do you want to do? [1 to 6] ";
		cin >> num;
		cin.ignore();
	} while (num <= 0 || num > 6);
	choiceManageUsersMain(num);
}

void Users::choiceManageUsersMain(int n) {
	if (n == 1) {
		userList();
	}
	else if (n == 2) {
		addNewUser();
	}
	else if (n == 3) {
		deleteUser();
	}
	else if (n == 4) {
		updateUser();
	}
	else if (n == 5) {
		findUser();
	}
	else {
		MainMenu menu;
		menu.mainScreen(false);
	}
	cout << "\n\t\t\tPress enter to return to the manage users menu...\n";
	cin.get();
	manageUsersScreen();
}
