#ifndef STUDENT_H
#define STUDENT_H

#include <uC++.h>

#include "Printer.h"
#include "NameServer.h"
#include "WATCardOffice.h"


_Task Student {
    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );
};

#endif //STUDENT_H
