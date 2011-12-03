#include <uC++.h>

#include "Student.h"

void Student::main() {

}


Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
		  unsigned int maxPurchases ) :
  printer(prt), nameServer(nameServer), cardOffice(cardOffice), id(id), maxPurchases(maxPurchases)
{
  
}
