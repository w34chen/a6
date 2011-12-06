#include <uC++.h>

#include "Bank.h"
#include <iostream>

using namespace std;

Bank::Bank( unsigned int numStudents ) : numStudents(numStudents) {
  accounts.resize(numStudents, 0);
  lockList = new uCondition[numStudents];
}


void Bank::deposit( unsigned int id, unsigned int amount ) {
  accounts.at(id) += amount;
  if (!lockList[id].empty() && accounts.at(id) >= lockList[id].front())
    lockList[id].signal();
}
 
void Bank::withdraw( unsigned int id, unsigned int amount ) {
  if (accounts.at(id) < amount) {
    lockList[id].wait(amount);
  }
  accounts.at(id) -= amount;
}

Bank::~Bank() {
  delete[] lockList;
}
