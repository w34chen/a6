#include "NameServer.h"
#include <iostream>

using namespace std;

//NameServer constructor. Initialize all variables and assign a vending machine to a student
//according to their IDs
NameServer::NameServer( Printer &prt, unsigned int numVendingMachines,
		unsigned int numStudents ) {
	pPrt = &prt;
	numMachines = numVendingMachines;
	numStuds = numStudents;
	addedMachines = 0;
	studVend.resize(numStudents);		//record the machine Id that's mapped to student per student
	machineList = new VendingMachine *[numVendingMachines];
	for (unsigned int i = 0; i < numStudents; i++)
		studVend[i] = i % numVendingMachines; //use % to wrap around
}
void NameServer::VMregister( VendingMachine *vendingmachine ) {
	unsigned int id = vendingmachine->getId();
	pPrt->print(Printer::NameServer, 'R', id);
	machineList[addedMachines] = vendingmachine; //record machines as they start
	addedMachines++;	//keep track of how many machines were registered for the index of the machineList array
}
VendingMachine * NameServer::getMachine( unsigned int id ) {
	VendingMachine *get;
	get = machineList[studVend[id]];
	pPrt->print(Printer::NameServer, 'N', id, get->getId());
	studVend[id] = (studVend[id]+1)%(addedMachines-1); //retrieve next machine for specific student
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
