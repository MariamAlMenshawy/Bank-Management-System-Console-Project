#pragma once
#include<iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

static int ID = 1;

class Time {
    int id;
    double amount;
    string type;
    string currency;
    string date;
    string accountNumber;

public:

    Time(string t, double a, string c, string accNum) {
        type = t;
        amount = a;
        currency = c;
        accountNumber = accNum;

        time_t now = time(0);
        tm localTime;
        localtime_s(&localTime, &now);
        stringstream ss;
        ss << put_time(&localTime, "%Y-%m-%d %H:%M:%S");
        date = ss.str();

        id = ID++;

        ofstream file("Transactions.txt", ios::app);
        file << accountNumber << "||" << type << "||" << amount << "||"
            << currency << "||" << date << endl;
        file.close();
    }
    Time() {}
    string AccountNumber() { return accountNumber; }
    string Type() { return type; }
    double Amount() { return amount; }
    string Currency() { return currency; }
    string Date() { return date; }
    
    Time convertLineToData(string& line, string sep="||");
};
