#ifndef BANK_H
#define BANK_H

#include <uC++.h>

_Monitor Bank {
  public:
    Bank( unsigned int numStudents );
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
};

#endif // BANK_H
