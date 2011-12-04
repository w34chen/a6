#include <uC++.h>

#include "Student.h"
#include "NameServer.h"

void Student::main() {
  // Generate how many times student is going to purchase soda
  // range: [1, MaxPurchase]
  
  // Select a random flavor [0,3]

  // Create a new WATCard with $5 balance

  // Obtain location to vending machine from name server

  // Loop through all the attempts to purchase soda
  
  // Yield before purchase soda
  
  // Purchase sode from vending machine

  // Drink soda

  // Insufficient funds

  // Transfer soda-code plus $5 to WATCard via WATCard office

  // Vending machine out of flavor

  // Obtain new vending machine from name server

  // WATCard is lost
  // Delete old WATCard
  // Create new WATCard

}


Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
		  unsigned int maxPurchases ) :
  printer(prt), nameServer(nameServer), cardOffice(cardOffice), id(id), maxPurchases(maxPurchases)
{
  
}
