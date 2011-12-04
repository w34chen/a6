#ifndef TRUCK_H
#define TRUCK_H

#include <uC++.h>

#include "Printer.h"
#include "NameServer.h"
#include "BottlingPlant.h"

_Task Truck {
	Printer *pPrt;
	NameServer *server;
	BottlingPlant *plant;
	unsigned int numVendingMachines;
	unsigned int maxStockPerFlavour;
    void main();
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) :
        	   pPrt(&prt), server(&nameServer), plant(&plant),
        	   numVendingMachines(numVendingMachines),
        	   maxStockPerFlavour(maxStockPerFlavour){};
};

#endif // TRUCK_H
