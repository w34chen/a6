#include <uC++.h>

#include "Bank.h"
#include <iostream>

using namespace std;

Bank::Bank( unsigned int numStudents ) : numStudents(numStudents) {
  accounts.resize(numStudents, 0);
}


void Bank::deposit( unsigned int id, unsigned int amount ) {
	cout <<"deposit " <<amount <<" to " <<id;
  accounts.at(id) += amount;
  cout <<" deposited amount is " <<accounts.at(id) <<endl;
}
 
void Bank::withdraw( unsigned int id, unsigned int amount ) {
	cout <<"withdraw from " <<id <<" with " <<amount <<endl;
  while (accounts.at(id) < amount) _Accept(deposit);
  accounts.at(id) -= amount;
  cout <<id <<" withdrawn amount is " <<accounts.at(id) <<endl;
}
