#include "NameServer.h"

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
	VendingMachine *get = machineList[studVend[id]];
	pPrt->print(Printer::NameServer, 'N', id, get->getId());
	studVend[id]++;
	return get;
}
VendingMachine ** NameServer::getMachineList() {
	return machineList;
}

void NameServer::main() {
	pPrt->print(Printer::NameServer, 'S');
	for (;;) {
		cout <<"inside nameServer main for loop" <<endl;
		_Accept(~NameServer) {
			break;
		} or _Accept(VMregister, getMachine, getMachineList) {
			cout <<"inside nameServer accept buy and inventory" <<endl;
		}
	}
	pPrt->print(Printer::NameServer, 'F');
}
