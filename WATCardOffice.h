#ifndef WATCARDOFFICE_H
#define WATCARDOFFICE_H

#include <uC++.h>
#include <vector>
#include <stack>
#include <iostream>

#include "WATCard.h"
#include "Bank.h"
#include "Printer.h"
#include "mprng.h"

extern MPRNG mprng_;

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
      WATCardOffice* const cardOffice;
      Printer& printer;
      Job* job;
      void main() {
	// Printe: Courier Start
	printer.print(Printer::Courier, 'S');

	for (;;) {
	  _Accept(~Courier) {
	    // Pinter:Courier Finish
	    printer.print(Printer::Courier, 'F');	    
	  }
	  else {
	    // Request work
	    job = cardOffice->requestWork();
	  
	    // Extract parameters from job
	    unsigned int id = job->args.id;
	    unsigned int amount = job->args.amount;
	    WATCard* watcard = job->args.watcard;
	    
	    // Pinter:Courier Start fund transfer
	    printer.print(Printer::Courier, 't', id, amount);
	    
	    // Transfer fond from bank
	    bank.withdraw(id, amount);

	    // Deposit money into watcard
	    watcard->deposit(amount);

	    // Pinter:Courier Complete fund transfer
	    printer.print(Printer::Courier, 'T', id, amount);

	    // Randomly lost WATCard
	    bool loseWATCard = ( mprng_(6) == 0);
	    if (loseWATCard) {
	      Lost* lost = new Lost();
	      job->result.exception(lost);
	    }

	    // Deliver the real watcard pointer for the future
	    job->result.delivery(watcard);

	    delete job;
	  } // else
	} // for loop
      }
    public:
    Courier(Bank& bank, WATCardOffice* const cardOffice, Printer& printer) : 
      bank(bank), cardOffice(cardOffice), printer(printer) 
      {
	job = NULL;
      }
      ~Courier() {}
    };

    void main();

    Printer &printer;
    Bank &bank;
    unsigned int numCouriers;
    std::vector<Courier*> workers;
    std::stack<Job*> jobs;
  public:
    _Event Lost {};
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    ~WATCardOffice();
    FWATCard create( unsigned int sid, unsigned int amount, WATCard *&card );
    FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};


#endif // WATCARDOFFICE_H
