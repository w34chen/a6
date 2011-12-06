#include "Truck.h"
#include "mprng.h"

using namespace std;

extern MPRNG mprng_;

void Truck::main() {
    unsigned int cargo[4]; // if want to declare as cargo[...] need a number in ...
    unsigned int *currentStock;
    unsigned int addStock;
    unsigned int notReplenished;
	pPrt->print(Printer::Truck, 'S');
	for (;;) {
		//obtain location of vending machine from name server
		VendingMachine **machineList = server->getMachineList();

		yield(mprng_(1, 10));

		if (plant->getShipment(cargo))
			break;
		pPrt->print(Printer::Truck, 'P', cargo[0]+cargo[1]+cargo[2]+cargo[3]);

		for (unsigned int i = 0; i < numVendingMachines; i++){ //loop through all machines

			notReplenished = 0;
			currentStock = &(*machineList[i]->inventory());  //get existing amount in machines
			pPrt->print(Printer::Truck, 'd', machineList[i]->getId(), cargo[0]+cargo[1]+cargo[2]+cargo[3]);
			for (unsigned int j = 0; j < 4; j++) { //loop through all flavours
				addStock = maxStockPerFlavour - currentStock[j]; //amount to replenish

				if (addStock) {
						if (cargo[j] > addStock) {
						currentStock[j] += addStock;
						cargo[j] -= addStock;
					} else {
						currentStock[j] += cargo[j];
						cargo[j] = 0;
						notReplenished += maxStockPerFlavour - currentStock[j];
					}
				}

			}
			if (notReplenished)
				pPrt->print(Printer::Truck, 'U', machineList[i]->getId(), notReplenished);
			else
				pPrt->print(Printer::Truck, 'D', machineList[i]->getId(), cargo[0]+cargo[1]+cargo[2]+cargo[3]);
			machineList[i]->restocked(); //don't knwo what's wrong with this line! =(
		}
	}
	pPrt->print(Printer::Truck, 'F');
}
