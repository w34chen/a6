#ifndef WATCARDOFFICE_H
#define WATCARDOFFICE_H

#include <uC++.h>
#include <vector>

#include "WATCard.h"
#include "Bank.h"
#include "Printer.h"

_Task WATCardOffice {
  struct Args {
    unsigned int id;
    unsigned int amount;
    WATCard* watcard;
  };
    struct Job {				// marshalled arguments and return future
	Args args;				// call arguments (YOU DEFINE "Args")
	FWATCard result;			// return future
	Job( Args args ) : args( args ) {}
    };
    _Task Courier { //communicate with bank
      Bank& bank;

      void main() {
	// Request work
	
	// Randomly lost WATCard 
      }
    Courier(Bank& bank) : bank(bank) {
      }
      
    };

    void main();

    Printer &printer;
    Bank &bank;
    unsigned int numCouriers;
    std::vector<Courier*> workers;
  public:
    _Event Lost {};
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    FWATCard create( unsigned int sid, unsigned int amount, WATCard *&card );
    FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};


#endif // WATCARDOFFICE_H
