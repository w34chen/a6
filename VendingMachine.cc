#include "VendingMachine.h"
#include <iostream>

using namespace std;

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id,
		unsigned int sodaCost, unsigned int maxStockPerFlavour ) {
	pPrt = &prt;
	server = &nameServer;
	ID = id;
	Cost = sodaCost;
	maxStock = maxStockPerFlavour;
	for (int i = 0; i < 4; i++)
		stock[i] = 0;
}

VendingMachine::Status VendingMachine::buy( Flavours flavour, WATCard &card ) {
	if (!stock[(int)flavour])
		return STOCK;
	if (card.getBalance() < Cost)
		return FUNDS;
	card.withdraw(Cost);
	stock[(int)flavour]--;
	pPrt->print(Printer::Vending, ID, 'B', flavour, stock[(int)flavour]--);
	return BUY;
}

unsigned int * VendingMachine::inventory() {
	//cout <<"called " <<ID <<" inventory: " <<stock <<" " <<&stock[0] <<" " <<&stock[1] <<" " <<&stock[2] <<" " <<&stock[3] <<endl;
	pPrt->print(Printer::Vending, ID, 'r');
	restocking = true;
	return stock;
}

void VendingMachine::restocked() {
	//cout <<"called VendingMachine::restocked" <<endl;
	restocking = false;
	pPrt->print(Printer::Vending, ID, 'R');
}

_Nomutex unsigned int VendingMachine::cost() { return Cost; }

_Nomutex unsigned int VendingMachine::getId() { return ID; }

void VendingMachine::main() {
	pPrt->print(Printer::Vending, ID, 'S', Cost);
	server->VMregister(this);
	for (;;) {
		_Accept(~VendingMachine) {
			break;
		} or _When(!restocking) _Accept(buy, inventory) {
		} or _When(restocking) _Accept(restocked) {
		}
	}
	pPrt->print(Printer::Vending, ID, 'F');
}
