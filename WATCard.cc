#include <uC++.h>

#include "WATCard.h"
#include <iostream>

using namespace std;

WATCard::WATCard() {
  balance = 0;
}

void WATCard::deposit( unsigned int amount ) {
	//cout <<"deposit " <<amount <<" to watcard" <<endl;
  // use courier to deposit
  balance += amount;
  //cout <<"new watcard balance: " <<balance <<endl;
}

void WATCard::withdraw( unsigned int amount ) {
  // withdraw money from WATCard
	//cout <<"withdraw " <<amount <<" from watcard" <<endl;
  balance -= amount;
  //cout <<"new watcard balance: " <<balance <<endl;
}

unsigned int WATCard::getBalance() {
	//cout <<"getbalance: " <<balance <<endl;
  return balance;
}
