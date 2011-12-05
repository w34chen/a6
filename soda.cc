#include "soda.h"
#include "Printer.h"
#include "WATCard.h"
#include "NameServer.h"
#include "VendingMachine.h"
#include "BottlingPlant.h"
#include "Truck.h"
#include "Bank.h"
#include "Student.h"
#include "Parent.h"

#include "mprng.h"

MPRNG mprng_;

void uMain::main() {

	unsigned int numStudents=2, numVendingMachines=2, numCouriers=1;
	unsigned int maxPurchases = 3, parentalDelay = 20;
	
	seed = 3;

	mprng_.seed(seed);

	Printer prt(numStudents,numVendingMachines,numCouriers);

	Bank bank(numStudents);

	Parent parent(prt, bank, numStudents, parentalDelay );

	WATCardOffice cardOffice(prt, bank, numCouriers ); //the couriers are created by the WATCard ofﬁce.

	NameServer nameServer(prt, numVendingMachines, numStudents );

	VendingMachine *vendingMachine[numVendingMachines];
	for (unsigned int i = 0; i < numVendingMachines; i++)
		vendingMachine[i] = new VendingMachine(prt, nameServer, i, SodaCost, MaxStockPerFlavour );
	cout <<"umain: max stock per flavour: " <<MaxStockPerFlavour <<endl;
	BottlingPlant *bottlingPlant = new BottlingPlant(prt, nameServer, numVendingMachines,MaxShippedPerFlavour,
			MaxStockPerFlavour, TimeBetweenShipments ); //truck is created by the bottling plant

	Student *student[numStudents];
	for (unsigned int i = 0; i < numStudents; i++)
		student[i] = new Student(prt, nameServer, cardOffice, i, maxPurchases );

	for (unsigned int i = 0; i < numStudents; i++)
		delete(student[i]);

	delete(bottlingPlant);

	for (unsigned int i = 0; i < numVendingMachines; i++)
		delete(vendingMachine[i]);


}
