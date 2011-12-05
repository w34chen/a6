#include <uC++.h>

#include "Student.h"
#include "NameServer.h"
#include "WATCard.h"
#include "VendingMachine.h"
#include "mprng.h"

using namespace std;

extern MPRNG mprng_;

void Student::main() {
  // Generate how many times student is going to purchase soda
  // range: [1, MaxPurchase]
  unsigned int numOfSoda = mprng_(1, maxPurchases);
  cout <<id <<" student main numOfSoda " <<numOfSoda <<endl;
  // Select a random flavor [0,3]
  VendingMachine::Flavours favFlavour = (VendingMachine::Flavours)mprng_(0,3);

  // Printer: Student Start Favourite soda Num of bottle
  printer.print(Printer::Student, id, 'S', favFlavour, numOfSoda);

  // Create a new WATCard with $5 balance
  WATCard* card = new WATCard();
  FWATCard fCard = cardOffice.create(id, 5, card);
  cout <<id <<" created watcard " <<endl;
  // Obtain location to vending machine from name server
  VendingMachine* vendingMachine = nameServer.getMachine(id);
  cout <<id <<" got vending machine with id " <<vendingMachine->getId() <<endl;
  // Printer: Student Select vending machine
  printer.print(Printer::Student, id, 'V', vendingMachine->getId());
  
  // Loop through all the attempts to purchase soda
  for (unsigned int i = 0; i < numOfSoda; i++) {
    // Yield before purchase soda
    unsigned int yieldTime = mprng_(1, 10);
    yield(yieldTime);
  
    while (true) { // Will busy waiting to try buy soda unless succeeded
      try {
	_Enable {
		cout <<id <<" inside student enable block " <<endl;
	  // Purchase sode from vending machine
	  VendingMachine::Status status = vendingMachine->buy(favFlavour, *(fCard()));
	  cout <<id <<" got machine status" <<endl;
	  if (status == VendingMachine::FUNDS) { // Insufficient funds
		  cout <<id <<" status is FUNDS" <<endl;
	    // Transfer soda-code plus $5 to WATCard via WATCard office
	    cardOffice.transfer(id, 5 + vendingMachine->cost(), fCard);
	  } else if (status == VendingMachine::STOCK) { // Vending machine out of flavor
		  cout <<id <<" status is STOCK" <<endl;
	    // Obtain new vending machine from name server
	    vendingMachine = nameServer.getMachine(id);
	    // Printer: Student Select vending machine
	    printer.print(Printer::Student, id, 'V', vendingMachine->getId());
	  } else { // status == BUY, successful purchase
		  cout <<id <<" status is normal" <<endl;
	    goto L1; // jump out of buying loop
	  }	
	}
      } catch (WATCardOffice::Lost) {
	// WATCard is lost
	// Printer: Student Watcard is lost
    	  cout <<"watcard is lost" <<endl;
	printer.print(Printer::Student, id, 'L');

	// Delete old WATCard
	delete card;

	// Create new WATCard
	fCard = cardOffice.create(id, 5, card);
      }
    } // while loop
  L1:; // Successfully bought soda
    // Drink soda
    // Printer: Student Bought a soda
    printer.print(Printer::Student, id, 'B', card->getBalance());
    cout <<id <<" student bought soda remaining balance: " <<card->getBalance() <<endl;
    
  } // for loop
  
  // Printer: Student Finished
  printer.print(Printer::Student, id, 'F');
}


Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
		  unsigned int maxPurchases ) :
  printer(prt), nameServer(nameServer), cardOffice(cardOffice), id(id), maxPurchases(maxPurchases)
{
  
}
