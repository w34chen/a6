#include "BottlingPlant.h"

bool BottlingPlant::getShipment( unsigned int cargo[] ) {

}

void BottlingPlant::main() {
	pPrt->print(Printer::BottlingPlant, 'S');
	Truck *truck = new Truck(pPrt, server, &this);
	for (;;) {
		yield(timeBetweenShipments);

		cout <<"inside nameServer main for loop" <<endl;
		_Accept(~NameServer) {
			break;
		} or _Accept(VMregister, getMachine, getMachineList) {
			cout <<"inside nameServer accept buy and inventory" <<endl;
		}
	}
	pPrt->print(Printer::BottlingPlant, 'F');
}
