#include<iostream>
#include<fstream>
#include<sstream>
#include"loginScreen.h"
#include"Users.h"
#include"MainMenu.h"
using namespace std;

void loginScreen::login() {
	cout <<"\t\t\t" << string(50, '_') << endl<<endl;
	cout << "\t\t\t\t\t  Login Screen\n";
	cout << "\t\t\t" << string(50, '_') << endl;
}
bool loginScreen::checkUser() {
	
	string userName, passWord;
	cout << "\t\t\tUsername: "; 
	cin >> userName;
	cout << "\t\t\tPassword: ";
	cin >> passWord;

	ifstream users("Users.txt");
	string line;
	while (getline(users, line)) {
		Users u=Users::convertLineToData(line);
		if (userName == u.Username() && passWord == u.Password()) {
			
			MainMenu m;
		    m.mainScreen(true);
			
			return true;
			break;
		}		
	}
	return false;
}
void loginScreen::yourTries() {
	int t = 2;
	while (t != 0) {
		cout << "\t\t\tInvalid username or password.\n ";
		cout << "\t\t\tYou have " << t << " attempts before the program closes.\n\n";
		
		if (checkUser()) {
			break;
		}
		t--;
	}
}
