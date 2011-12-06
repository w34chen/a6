#include <uC++.h>

#include "WATCard.h"
#include <iostream>

using namespace std;

WATCard::WATCard() {
  balance = 0;
}

void WATCard::deposit( unsigned int amount ) {
  // use courier to deposit
  balance += amount;
}

void WATCard::withdraw( unsigned int amount ) {
  // withdraw money from WATCard
  balance -= amount;
}

unsigned int WATCard::getBalance() {
  return balance;
}
