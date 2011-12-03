#include "Truck.h"

void Truck::main() {
	unsigned int cargo[];
	pPrt->print(Printer::Truck, 'S');
	for (;;) {
		//obtain location of vending machine from name server
		VendingMachine **machineList = plant->getMachineList();
		yield(timeBetweenShipments);
		if (plant->getShipment(cargo))
			break;
		for (int i = 0; i < numVendingMachines; i++){
			machineList[i]->inventory();
			//transfer cargo

		}
		cout <<"inside nameServer main for loop" <<endl;
	}
	pPrt->print(Printer::Truck, 'F');
}
