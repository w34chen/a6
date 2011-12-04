#ifndef NAMESERVER_H
#define NAMESERVER_H

#include <uC++.h>
#include <vector>

#include "VendingMachine.h"
#include "Printer.h"

_Task VendingMachine;

_Task NameServer {
	Printer *pPrt;
	unsigned int numMachines;
	unsigned int numStuds;
	unsigned int addedMachines;
	VendingMachine **machineList;
	std::vector<unsigned int> studVend;
    void main();
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};

#endif // NAMESERVER_H
