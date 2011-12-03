#ifndef PARENT_H
#define PARENT_H

#include <uC++.h>

_Task Parent {
    void main();
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};


#endif // PARENT_H
