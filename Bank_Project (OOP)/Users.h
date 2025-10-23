#pragma once
#include<iostream>

using namespace std;
class Users
{
private:
	string fullName;
	string email;
	string username;
	string password;
public:
	string FullName() { return fullName; }
	string Email() { return email; }
	string Username() { return username; }
	string Password() { return password; }

    static string convertDataToLine(Users& data, string sep = "||");
	static Users convertLineToData(string& line, string sep = "||");

	void AddOrUpdate();
	bool Delete(string name);
	void userList();
	void addNewUser();
	void deleteUser();
	void updateUser();
	void findUser();

	void manageUsersScreen();
	void choiceManageUsersMain(int n);
	
};
