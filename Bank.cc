#include <uC++.h>

#include "Bank.h"

Bank::Bank( unsigned int numStudents ) : numStudents(numStudents) {
  account.resize(numStudents, 0);
}


void Bank::deposit( unsigned int id, unsigned int amount ) {

}
 
void Bank::withdraw( unsigned int id, unsigned int amount ) {

}
