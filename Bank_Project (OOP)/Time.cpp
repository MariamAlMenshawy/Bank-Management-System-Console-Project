#include"Time.h"
#include<iostream>

using namespace std;



Time Time:: convertLineToData(string& line, string sep) {
    Time t;

    size_t pos1 = line.find(sep);
    size_t pos2 = line.find(sep, pos1 + sep.size());
    size_t pos3 = line.find(sep, pos2 + sep.size());
    size_t pos4 = line.find(sep, pos3 + sep.size());
    size_t pos5 = line.find(sep, pos4 + sep.size());

    t.accountNumber = line.substr(0, pos1);
    t.type = line.substr(pos1 + sep.size(), pos2 - pos1 - sep.size());
    string am = line.substr(pos2 + sep.size(), pos3 - pos2 - sep.size());
    t.amount = stod(am);
    t.currency = line.substr(pos3 + sep.size(), pos4 - pos3 - sep.size());
    t.date = line.substr(pos4 + sep.size());

    return t;
}

