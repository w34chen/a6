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
		stock[i] = 0;	//initialize the value of vending machine stock
}

VendingMachine::Status VendingMachine::buy( Flavours flavour, WATCard &card ) {
	if (stock[(int)flavour] < 1)
		return STOCK;
	if (card.getBalance() < Cost)
		return FUNDS;
	card.withdraw(Cost); //if there is stock and there's enough funds on the card, withdraw money
	stock[(int)flavour]--; //update stock count
	pPrt->print(Printer::Vending, ID, 'B', flavour, stock[(int)flavour]);
	return BUY;
}

unsigned int * VendingMachine::inventory() {
	pPrt->print(Printer::Vending, ID, 'r');
	restocking = true; //set flag so only accept calsl to restocked
	return stock;
}

void VendingMachine::restocked() {
	restocking = false; //reset flag so VendingMachine will accept calls to Inventory and buy as well
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
