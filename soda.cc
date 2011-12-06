#include <uC++.h>
#include <sstream>

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
#include "config.h"

#include "mprng.h"

MPRNG mprng_;

using namespace std;

bool convert( int &val, char *buffer ) {		// convert C string to integer
    std::stringstream ss( buffer );			// connect stream and buffer
    ss >> dec >> val;					// convert integer from buffer
    return ! ss.fail() &&				// conversion successful ?
	// characters after conversion all blank ?
	string( buffer ).find_first_not_of( " ", ss.tellg() ) == string::npos;
} // convert

void usage( char *argv[] ) {
  cerr << "Usage: " << argv[0] << " [ config-file [ random-seed ] ]" << endl;
  exit( EXIT_FAILURE );				// TERMINATE
} // usage

void uMain::main() {

  int seed = getpid();
  ConfigParms config;
  
  switch ( argc ) {
  case 3:
    if ( ! convert( seed , argv[2] ) || seed < 0) {	// invalid integer ?
      usage( argv );
	} // if
    // FALL THROUGH
  case 2:
    processConfigFile( argv[1], config );
    break;
  case 1:
    processConfigFile( "soda.config", config);
    break;
    // all defaults
  default:						// wrong number of options
    usage( argv );
  } // switch

	mprng_.seed(seed);

	Printer prt(config.numStudents,config.numVendingMachines,config.numCouriers);

	Bank bank(config.numStudents);

	Parent parent(prt, bank, config.numStudents, config.parentalDelay );

	WATCardOffice cardOffice(prt, bank, config.numCouriers ); //the couriers are created by the WATCard ofﬁce.

	NameServer nameServer(prt, config.numVendingMachines, config.numStudents );

	VendingMachine *vendingMachine[config.numVendingMachines];
	for (unsigned int i = 0; i < config.numVendingMachines; i++)
		vendingMachine[i] = new VendingMachine(prt, nameServer, i, config.sodaCost, config.maxStockPerFlavour );
	BottlingPlant *bottlingPlant = new BottlingPlant(prt, nameServer, config.numVendingMachines,config.maxShippedPerFlavour,
			config.maxStockPerFlavour, config.timeBetweenShipments ); //truck is created by the bottling plant

	Student *student[config.numStudents];
	for (unsigned int i = 0; i < config.numStudents; i++)
		student[i] = new Student(prt, nameServer, cardOffice, i, config.maxPurchases );

	for (unsigned int i = 0; i < config.numStudents; i++)
		delete(student[i]);

	delete(bottlingPlant);

	for (unsigned int i = 0; i < config.numVendingMachines; i++)
		delete(vendingMachine[i]);


}
