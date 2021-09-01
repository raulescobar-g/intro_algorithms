#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Account{
    public:
        Account(double starting_capital);
        Account(const Account& acc);
        ~Account();

        //returns 1,0 for fail or success
        int buy(string ticker, int share_count, double price);
        int sell(string ticker, int share_count, double price); 

        //returns value of securities and capital
        double state(); 

    private:
        double balance;
        vector<string> securities;
        vector<int> shares;
        vector<double> value;
};

#endif