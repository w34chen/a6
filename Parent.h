#ifndef PARENT_H
#define PARENT_H

#include <uC++.h>

#include "Printer.h"
#include "Bank.h"

_Task Parent {
  Printer &printer;
  Bank &bank;
  unsigned int numStudents;
  unsigned int parentalDelay;
  
    void main();
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};


#endif // PARENT_H
