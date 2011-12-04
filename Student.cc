#include <uC++.h>

#include "Student.h"
#include "NameServer.h"
#include "WATCard.h"
#include "VendingMachine.h"
#include "mprng.h"

extern MPRNG mprng_;

void Student::main() {
  // Generate how many times student is going to purchase soda
  // range: [1, MaxPurchase]
  unsigned int numOfSoda = mprng_(1, maxPurchases);
  
  // Select a random flavor [0,3]
  VendingMachine::Flavours favFlavour = (VendingMachine::Flavours)mprng_(0,3);

  // Create a new WATCard with $5 balance
  WATCard* card;
  FWATCard fCard = cardOffice.create(id, 5, card);

  // Obtain location to vending machine from name server
  VendingMachine* vendingMachine = nameServer.getMachine(id);
  
  // Loop through all the attempts to purchase soda
  for (unsigned int i = 0; i < numOfSoda; i++) {
    // Yield before purchase soda
    unsigned int yieldTime = mprng_(1, 10);
    yield(yieldTime);
  
    while (true) { // Will busy waiting to try buy soda unless succeeded
      try {
	_Enable {
	  // Purchase sode from vending machine
	  VendingMachine::Status status = vendingMachine->buy(favFlavour, *(fCard()));
	  
	  if (status == VendingMachine::FUNDS) { // Insufficient funds
	    // Transfer soda-code plus $5 to WATCard via WATCard office
	    cardOffice.transfer(id, 5, fCard);

	  } else if (status == VendingMachine::STOCK) { // Vending machine out of flavor
	    // Obtain new vending machine from name server
	    vendingMachine = nameServer.getMachine(id);

	  } else { // status == BUY, successful purchase
	    goto L1; // jump out of buying loop
	  }	
	}
      } catch (WATCardOffice::Lost) {
	// WATCard is lost
	// Delete old WATCard
	// Create new WATCard
      }
    } // while
  L1:; // Successfully bought soda
    // Drink soda

  } // for
}


Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
		  unsigned int maxPurchases ) :
  printer(prt), nameServer(nameServer), cardOffice(cardOffice), id(id), maxPurchases(maxPurchases)
{
  
}
