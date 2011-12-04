#include "soda.h"
#include "Printer.h"
#include "WATCard.h"
#include "NameServer.h"
#include "VendingMachine.h"

#include "mprng.h"

MPRNG mprng_;

void uMain::main() {

	unsigned int numStudents=2, numVendingMachines=2, numCouriers=1;
	seed = 3;

	mprng_.seed(seed);

	Printer prt(numStudents,numVendingMachines,numCouriers);

	//Bank bank(numStudents);

	//Parent parent(prt, bank, numStudents, parentalDelay );

	//WATCardOffice cardOffice(prt, bank, numCouriers ); //the couriers are created by the WATCard ofﬁce.

	NameServer nameServer(prt, numVendingMachines, numStudents );

	VendingMachine *vendingMachine[numVendingMachines];
	for (unsigned int i = 0; i < numVendingMachines; i++)
		vendingMachine[i] = new VendingMachine(prt, nameServer, i, SodaCost, MaxStockPerFlavour );

	unsigned int *inventory = vendingMachine[0]->inventory();
	cout <<"inventory " <<inventory[0] <<" " <<inventory[1] <<" " <<inventory[2] <<" " <<inventory[3] <<endl;

	inventory[0] = 3;
	inventory[1] = 3;
	inventory[2] = 3;
	inventory[3] = 3;

	WATCard *card = new WATCard();
	vendingMachine[0]->restocked();
	vendingMachine[0]->buy(VendingMachine::CREAM, *card);


	//BottlingPlant *bottlingPlant = new BottlingPlant(prt, nameServer, numVendingMachines,maxShippedPerFlavour,
	//		maxStockPerFlavour, timeBetweenShipments ); //truck is created by the bottling plant

	//Student *student[numStudents];
	//for (int i = 0; i < numStudents; i++)
	//	student[i] = new Student(prt, nameServer, cardOffice, i, maxPurchases );

	//for (int i = 0; i < numStudents; i++)
	//	delete(student[i]);

	//delete(bottlingPlant);

	//for (int i = 0; i < numVendingMachines; i++)
	//	delete(vendingMachine[i]);


}
