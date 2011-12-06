#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H

#include <uC++.h>

#include "NameServer.h"
#include "Printer.h"
#include "WATCard.h"

_Task NameServer;

_Task VendingMachine {
	unsigned int ID;		//vending machine location
	unsigned int Cost;		//unit cost per soda
	unsigned int maxStock;	//maximum stock per flavour
	Printer* pPrt;
	NameServer* server;
	unsigned int stock[4];	//current stock count
	bool restocking;		//used to control which calls it accepts
    void main();
  public:
    enum Flavours { CHERRY, CREAM, BEER, LIME }; 			// flavours of soda (YOU DEFINE)
    enum Status { BUY, STOCK, FUNDS };		// purchase status: successful buy, out of stock, insufficient funds
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    Status buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};

#endif // VENDINGMACHINE_H
