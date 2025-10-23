#include"SavingsAccount.h"
#include"BankAccount.h"
#include"Client.h"
#include<iostream>
#include <ctime>
#include <sstream>
#include <string>

using namespace std;

int SavingsAccount :: numberOfMonth(Client& c) {
	time_t now = time(0);
	tm localTime;
	localtime_s(&localTime, &now);
	stringstream ss;
	ss << put_time(&localTime, "%Y-%m-%d");
	string now_date = ss.str();
	int y1, m1, d1;
	int y2, m2, d2;

	char dash;
	stringstream ss1(c.Date());
	stringstream ss2(now_date);

	ss1 >> y1 >> dash >> m1 >> dash >> d1;
	ss2 >> y2 >> dash >> m2 >> dash >> d2;

	int monthNum = 0;
	int yearNum = 0;
	if (y2 > y1) {
		yearNum = y2 - y1;
	}
	monthNum = yearNum * 12;
	if (m2 > m1) {
		monthNum += (m2 - m1);
	}
	else if (m2 < m1) {
		monthNum -= (m1 - m2);
	}
	if (d2 < d1) 
		monthNum--;

	return monthNum;
}

double SavingsAccount::calculateMonthlyInterest(Client& c) {
	
	double monthlyRate = interestRate /12 / 100.0;
	int numOfMonth = numberOfMonth(c);
	double interest = c.Balance() * monthlyRate * numOfMonth;
	double new_balance = interest + c.Balance();
	
	return new_balance;
}