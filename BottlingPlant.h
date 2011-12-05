#ifndef BOTTLINGPLANT_H
#define BOTTLINGPLANT_H

#include <uC++.h>

#include "Printer.h"
#include "NameServer.h"

_Task Truck;

_Task BottlingPlant {
	Printer *pPrt;
	NameServer *server;
	unsigned int numVendingMachines;
	unsigned int maxShippedPerFlavour;
	unsigned int maxStockPerFlavour;
	unsigned int timeBetweenShipments;
	unsigned int producedStock[4];
	Truck *truck;
	uCondition pickup;
	bool destruct;
    void main();
  public:
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
    		unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
    		unsigned int timeBetweenShipments ) :
    			pPrt(&prt), server(&nameServer),
    			numVendingMachines(numVendingMachines),
    			maxShippedPerFlavour(maxShippedPerFlavour),
    			maxStockPerFlavour(maxStockPerFlavour),
    			timeBetweenShipments(timeBetweenShipments) {
    	destruct = false;
    };
    bool getShipment( unsigned int cargo[] );
    ~BottlingPlant();
};

#endif // BOTTLINGPLANT_H
