#include "BottlingPlant.h"
#include "Truck.h"
#include "mprng.h"

using namespace std;

extern MPRNG mprng_;

bool BottlingPlant::getShipment( unsigned int cargo[] ) {
	if (destruct) {
		cout <<"get shipment return true" <<endl;
		pickup.signal();
		return true;
	}
	for (int i = 0; i < 4; i++) {
		if (producedStock[i] > maxShippedPerFlavour) {
			cargo[i] = maxShippedPerFlavour;
			producedStock[i] -= maxShippedPerFlavour;
		} else {
			cargo[i] = producedStock[i];
			producedStock[i] = 0;
		}
	}
	//pickup.signal();
	//cout <<"bottling plant get shipment: unblocked" <<endl;
    return false;
}

BottlingPlant::~BottlingPlant() {
	destruct = true;
	pickup.wait();
	delete(truck);
}

void BottlingPlant::main() {
	pPrt->print(Printer::BottlingPlant, 'S');
	truck = new Truck(*pPrt, *server, *this, numVendingMachines, maxStockPerFlavour);
	for (int i = 0; i < 4; i++) {
		producedStock[i] = rand()%maxShippedPerFlavour;
		//cout <<"produced " <<i <<" flavour with quantity " <<producedStock[i] <<endl;
	}
	for (;;) {
		_Accept(~BottlingPlant) {
			break;
		} or _Accept (getShipment) {
			//cout <<"bottling plant main loop: about to yield " <<endl;
			yield(timeBetweenShipments);
			for (int i = 0; i < 4; i++) {
				producedStock[i] = rand()%maxShippedPerFlavour;
				//cout <<"produced " <<i <<" flavour with quantity " <<producedStock[i] <<endl;
			}
			pPrt->print(Printer::BottlingPlant, 'G', producedStock[0]+producedStock[1]+producedStock[2]+producedStock[3]);
			//pickup.wait();
			pPrt->print(Printer::BottlingPlant, 'P'); //this one might need to go in getShipment
		}
	}
	pPrt->print(Printer::BottlingPlant, 'F');
}
