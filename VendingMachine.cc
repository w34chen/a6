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
	//if (card.getBalance() < Cost)
	//	return FUND;
	//card.withdraw(Cost);
	stock[(int)flavour]--;
	pPrt->print(Printer::Vending, ID, 'B');
	return BUY;
}

unsigned int * VendingMachine::inventory() {
	cout <<"inside inventory " <<endl;
	pPrt->print(Printer::Vending, ID, 'r');
	restocking = true;
	return stock;
}

void VendingMachine::restocked() {
	cout <<"inside restocked " <<endl;
	restocking = false;
	pPrt->print(Printer::Vending, ID, 'R');
}

_Nomutex unsigned int VendingMachine::cost() { return Cost; }

_Nomutex unsigned int VendingMachine::getId() { return ID; }

void VendingMachine::main() {
	pPrt->print(Printer::Vending, ID, 'S');
	//server->VMregister(&this);
	for (;;) {
		cout <<"inside vendingMachine main for loop" <<endl;
		_Accept(~VendingMachine) {
			break;
		} or _When(!restocking) _Accept(buy, inventory) {
			cout <<"inside accept buy and inventory" <<endl;
		} or _When(restocking) _Accept(restocked) {
			cout <<"inside accept restocked" <<endl;
		}
	}
	pPrt->print(Printer::Vending, ID, 'F');
}
