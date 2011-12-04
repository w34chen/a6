#include "BottlingPlant.h"
#include "Truck.h"

using namespace std;

bool BottlingPlant::getShipment( unsigned int cargo[] ) {
  return false;
}

void BottlingPlant::main() {
	pPrt->print(Printer::BottlingPlant, 'S');
	Truck *truck = new Truck(*pPrt, *server, *this, 0, 0); // these last two numbers are numVendingMachines and maxStockPerFlavor);
	for (;;) {
		yield(timeBetweenShipments);
		/*
		  These code are from NameServer? -by Weiliang

		cout <<"inside nameServer main for loop" <<endl;
		_Accept(~NameServer) {
			break;
		} or _Accept(VMregister, getMachine, getMachineList) {
			cout <<"inside nameServer accept buy and inventory" <<endl;
		}
		*/
	}
	pPrt->print(Printer::BottlingPlant, 'F');
}
