#include "NameServer.h"
#include <iostream>

using namespace std;

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines,
		unsigned int numStudents ) {
	pPrt = &prt;
	numMachines = numVendingMachines;
	numStuds = numStudents;
	addedMachines = 0;
	studVend.resize(numStudents);
	machineList = new VendingMachine *[numVendingMachines];
	for (unsigned int i = 0; i < numStudents; i++)
		studVend[i] = i % numVendingMachines;
}
void NameServer::VMregister( VendingMachine *vendingmachine ) {
	unsigned int id = vendingmachine->getId();
	pPrt->print(Printer::NameServer, 'R', id);
	machineList[addedMachines] = vendingmachine;
	addedMachines++;
}
VendingMachine * NameServer::getMachine( unsigned int id ) {
	VendingMachine *get;
	get = machineList[studVend[id]];
	pPrt->print(Printer::NameServer, 'N', id, get->getId());
	studVend[id] = (studVend[id]+1)%(addedMachines-1);
	return get;
}
VendingMachine ** NameServer::getMachineList() {
	return machineList;
}

void NameServer::main() {
	pPrt->print(Printer::NameServer, 'S');
	for (;;) {
		_Accept(~NameServer) {
			break;
		} or _Accept(VMregister, getMachine, getMachineList) {
		}
	}
	pPrt->print(Printer::NameServer, 'F');
}

NameServer::~NameServer() {
  delete[] machineList;
}
