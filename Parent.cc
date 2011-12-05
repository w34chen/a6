#include <uC++.h>

#include "mprng.h"
#include "Parent.h"

extern MPRNG mprng_;

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) :
  printer(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay)
{
  
}

Parent::~Parent() {
  //Printer: Parent Finished
  printer.print(Printer::Parent, 'F');
}

void Parent::main() {

  // periodically gives a random amount of money [$1, $3] to a random student
  // Before each giftis transfered, the parent yields for parentalDelay times (not random). 
  // The parent must check for a call to its destructor to know when to terminate. 
  // Since it must not block on this call, it is necessary to use a terminating else on the accept statement. 
  // (Hence, the parent is busy waiting for the call to its destructor.)
  
  // Prints: Parent Start
  printer.print(Printer::Parent, 'S');
  
  for (;;) {
    _Accept (~Parent) {
      break;
    }
    else {
      // randomly generate amount of money to give
      unsigned int amount = mprng_(1, 3);
      
      //randomly generate which student to give money to
      unsigned int studentId = mprng_(numStudents - 1);

      // yield for parentalDelay
      yield(parentalDelay);

      bank.deposit(studentId, amount);
      // Printer:: Parent Deposit gift to Student and Amount
      printer.print(Printer::Parent, 'D', studentId, amount);
    }
  }
}
