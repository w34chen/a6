#ifndef STUDENT_H
#define STUDENT_H

#include <uC++.h>

#include "Printer.h"
#include "NameServer.h"
#include "WATCardOffice.h"


_Task Student {
    void main();
    
    Printer& printer;
    NameServer& nameServer;
    WATCardOffice cardOffice;
    unsigned int id;
    unsigned int maxPurchases;
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );
};

#endif //STUDENT_H
