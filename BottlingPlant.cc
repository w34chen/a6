#include "BottlingPlant.h"
#include "Truck.h"

using namespace std;

bool BottlingPlant::getShipment( unsigned int cargo[] ) {
	if (destruct) {
		cout <<"get shipment return true" <<endl;
		return true;
	}
	for (int i = 0; i < 4; i++)
		cargo[i] = producedStock[i];
	pickup.signal();
	//cout <<"bottling plant get shipment: unblocked" <<endl;
    return false;
}

void BottlingPlant::main() {
	pPrt->print(Printer::BottlingPlant, 'S');
	Truck truck(*pPrt, *server, *this, numVendingMachines, maxStockPerFlavour);
	for (;;) {
		_Accept(~BottlingPlant) {
			destruct = true;
			cout <<"destruct bottlingPlant" <<endl;
			break;
		} or _Accept (getShipment) {
			//cout <<"bottling plant main loop: about to yield " <<endl;
			yield(timeBetweenShipments);
			for (int i = 0; i < 4; i++) {
				producedStock[i] = rand()%maxShippedPerFlavour;
				//cout <<"produced " <<i <<" flavour with quantity " <<producedStock[i] <<endl;
			}
			pPrt->print(Printer::BottlingPlant, 'G', producedStock[0]+producedStock[1]+producedStock[2]+producedStock[3]);
			pickup.wait();
			pPrt->print(Printer::BottlingPlant, 'P'); //this one might need to go in getShipment
		}
	}
	pPrt->print(Printer::BottlingPlant, 'F');
}
