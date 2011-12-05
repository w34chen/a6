#include "Truck.h"

using namespace std;

void Truck::main() {
    unsigned int cargo[4]; // if want to declare as cargo[...] need a number in ...
    unsigned int *currentStock;
    unsigned int addStock;
    unsigned int notReplenished;
	pPrt->print(Printer::Truck, 'S');
	for (;;) {
		//obtain location of vending machine from name server
		VendingMachine **machineList = server->getMachineList();
		//cout <<"truck obtained vending machine list" <<endl;
		yield(rand()%10+1);
		//cout <<"truck finished yielding" <<endl;
		if (plant->getShipment(cargo))
			break;
		pPrt->print(Printer::Truck, 'P', cargo[0]+cargo[1]+cargo[2]+cargo[3]);
		cout <<"truck obtained shipment with cargo " <<cargo[0] <<" " <<cargo[1] <<" "
				<<cargo[2] <<" " <<cargo[3] <<endl;
		for (unsigned int i = 0; i < numVendingMachines; i++){ //loop through all machines
			cout <<"truck: machine " <<i <<endl;
			notReplenished = 0;
			currentStock = &(*machineList[i]->inventory());  //get existing amount in machines
			pPrt->print(Printer::Truck, 'd', machineList[i]->getId(), cargo[0]+cargo[1]+cargo[2]+cargo[3]);
			for (unsigned int j = 0; j < 4; j++) { //loop through all flavours
				addStock = maxStockPerFlavour - currentStock[j]; //amount to replenish
				cout <<j <<" cargo: " <<cargo[j] <<" currentStock: " <<currentStock[j] <<" addStock " <<addStock <<endl;
				if (cargo[j] > addStock) {
					currentStock[j] += addStock;
					cargo[j] -= addStock;
				} else {
					currentStock[j] += cargo[j];
					cargo[j] = 0;
					notReplenished += maxStockPerFlavour - currentStock[j];
				}
				cout <<" cargo left " <<cargo[j] <<" new currentStock: " <<currentStock[j]<<endl;
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
