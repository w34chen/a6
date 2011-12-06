#include "BottlingPlant.h"
#include "Truck.h"
#include "mprng.h"

using namespace std;

extern MPRNG mprng_;

bool BottlingPlant::getShipment( unsigned int cargo[] ) {
	if (destruct) {
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
	}
	for (;;) {
		_Accept(~BottlingPlant) {
			break;
		} or _Accept (getShipment) {
			yield(timeBetweenShipments);
			for (int i = 0; i < 4; i++) {
				producedStock[i] = rand()%maxShippedPerFlavour;
			}
			pPrt->print(Printer::BottlingPlant, 'G', producedStock[0]+producedStock[1]+producedStock[2]+producedStock[3]);
			pPrt->print(Printer::BottlingPlant, 'P'); //this one might need to go in getShipment
		}
	}
	pPrt->print(Printer::BottlingPlant, 'F');
}
