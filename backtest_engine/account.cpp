#include <iostream>
#include "account.h"
#include <vector>
#include <string>
using namespace std;


Account::Account(double starting_capital) {
    balance = starting_capital;
    value.push_back(starting_capital);
    cout<<'Account has been created with $'<<starting_capital<<endl;
}

Account::Account(const Account& acc){
    this->balance = acc.balance;
    this->value = acc.value;
    this->securities = acc.securities;
    this->shares = acc.shares;
    cout<<'Copying successfully.'<<endl;

}

Account::~Account(){
    cout<<'Destroying now.'<<endl;
}

//returns 1,0 for fail or success
int Account::buy(string ticker, int share_count, double price){
    if (share_count*price > balance){
        //maybe create an error class or have this output more specific errors in the future
        cout<<'ERROR: Attempted to exceed balance.'<<endl;
        cout<<'Current Balance: $'<<balance<<endl;
        cout<<'Price tag of '<<ticker<<': $'<<share_count*price<<endl;
        return 0;
    }

    for (int i = 0; i < securities.size(); ++i){
        if (ticker == securities[i]){
            balance -= price * share_count;
            return 1;
        }
    }
    securities.push_back(ticker);
    balance -= price * share_count;
    shares.push_back(share_count);
    return 1;
}

int Account::sell(string ticker, int share_count, double price){
    int loc = -1;
    for (int i = 0; i < securities.size(); ++i){
        if (securities[i] == ticker){
            loc = i;
        }
    }
    if (loc == -1 || share_count > shares[loc]){
        //maybe create an error class or have this output more specific errors in the future
        cout<<'ERROR: Attempted to exceed share count.'<<endl;
        cout<<'Current Shares for '<<ticker<<': '<<shares[loc]<<endl;
        return 0;
    }
    else{
        balance += price * share_count;
        shares[loc] -= share_count;
    }

}

//returns value of securities and capital
double Account::state(){
    double total = balance;
    for (int i = 0; i < securities.size(); ++i){
        total += shares[i]
    }
    return total;
} 

















