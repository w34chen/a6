#include <uC++.h>

#include "Bank.h"
#include <iostream>

using namespace std;

Bank::Bank( unsigned int numStudents ) : numStudents(numStudents) {
  accounts.resize(numStudents, 0);
}


void Bank::deposit( unsigned int id, unsigned int amount ) {
  accounts.at(id) += amount;
}
 
void Bank::withdraw( unsigned int id, unsigned int amount ) {
  while (accounts.at(id) < amount) _Accept(deposit);
  accounts.at(id) -= amount;
}
