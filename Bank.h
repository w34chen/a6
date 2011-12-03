#ifndef BANK_H
#define BANK_H

#include <uC++.h>
#include <vector>


_Monitor Bank {
  unsigned int numStudents;
  std::vector<unsigned int> accounts;

  public:
    Bank( unsigned int numStudents );
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
};

#endif // BANK_H
