#include <uC++.h>

#include "Parent.h"

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) :
  printer(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay)
{
  
}

Parent::~Parent() {
}

void Parent::main() {

  // periodically gives a random amount of money [$1, $3] to a random student
  // Before each giftis transfered, the parent yields for parentalDelay times (not random). 
  // The parent must check for a call to its destructor to know when to terminate. 
  // Since it must not block on this call, it is necessary to use a terminating else on the accept statement. 
  // (Hence, the parent is busy waiting for the call to its destructor.)

  for (;;) {
    _Accept (~Parent()) {
      break;
    }
    else {
      // generate money to give
      // yield
      
    }
  }
}
