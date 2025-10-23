#include<iostream>
#include"BankAccount.h"
#include"loginScreen.h"
#include"MainMenu.h"

using namespace std;
int main() {
	loginScreen s;
	s.login();
	if (!s.checkUser()) {
		s.yourTries();
	}
	
 }
