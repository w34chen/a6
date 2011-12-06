#include "BottlingPlant.h"
#include "Truck.h"
#include "mprng.h"

using namespace std;

extern MPRNG mprng_;

bool BottlingPlant::getShipment( unsigned int cargo[] ) {
	if (destruct) {			//if bottle plant is destructing, that means previous steps
		pickup.signal();	//woudl've blocked itself so it can wait for truck to destruct
		return true;
	}
	for (int i = 0; i < 4; i++) {
		if (producedStock[i] > maxShippedPerFlavour) {	//if there's stock left for next machine
			cargo[i] = maxShippedPerFlavour;			//max out current cargo
			producedStock[i] -= maxShippedPerFlavour;	//and find available stock for next
		} else {
			cargo[i] = producedStock[i];	//otherwise use all the leftover stock
			producedStock[i] = 0;
		}
	}
    return false;
}

BottlingPlant::~BottlingPlant() {
	destruct = true;
	pickup.wait();		//destructing, wait for truck to destruct incase truck calls getShipment
	delete(truck);
}

void BottlingPlant::main() {
	pPrt->print(Printer::BottlingPlant, 'S');
	truck = new Truck(*pPrt, *server, *this, numVendingMachines, maxStockPerFlavour);
	for (int i = 0; i < 4; i++) {
		producedStock[i] = mprng_(0, maxShippedPerFlavour);
	}
	for (;;) {
		_Accept(~BottlingPlant) {
			break;
		} or _Accept (getShipment) {
			yield(timeBetweenShipments);
			for (int i = 0; i < 4; i++) {
				producedStock[i] = mprng_(0, maxShippedPerFlavour);
			pPrt->print(Printer::BottlingPlant, 'G', producedStock[0]+producedStock[1]+producedStock[2]+producedStock[3]);
			pPrt->print(Printer::BottlingPlant, 'P'); //this one might need to go in getShipment
		}
	}
	pPrt->print(Printer::BottlingPlant, 'F');
}
