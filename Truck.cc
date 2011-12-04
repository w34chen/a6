#include "Truck.h"

using namespace std;

void Truck::main() {
  unsigned int* cargo; // if want to declare as cargo[...] need a number in ...
	pPrt->print(Printer::Truck, 'S');
	for (;;) {
		//obtain location of vending machine from name server
		VendingMachine **machineList = server->getMachineList();
		yield(0 /*timeBetweenShipments is not yet declared here*/);
		if (plant->getShipment(cargo))
			break;
		for (unsigned int i = 0; i < numVendingMachines; i++){
			machineList[i]->inventory();
			//transfer cargo

		}
		cout <<"inside nameServer main for loop" <<endl;
	}
	pPrt->print(Printer::Truck, 'F');
}
