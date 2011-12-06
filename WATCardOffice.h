#ifndef WATCARDOFFICE_H
#define WATCARDOFFICE_H

#include <uC++.h>
#include <vector>
#include <list>
#include <iostream>

#include "WATCard.h"
#include "Bank.h"
#include "Printer.h"
#include "mprng.h"

using namespace std;

extern MPRNG mprng_;

_Task WATCardOffice {
  struct Args {
    unsigned int id;
    unsigned int amount;
    WATCard* watcard;
  Args( unsigned int id, unsigned int amount, WATCard* watcard) :
    id(id), amount(amount), watcard(watcard){ }
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
      unsigned int id;
      Job* job;
      void main() {
	// Printe: Courier Start
	printer.print(Printer::Courier, id, 'S');

	for (;;) {
	  _Accept(~Courier) {
	    // Pinter:Courier Finish
	    printer.print(Printer::Courier, id, 'F');	    
	  }
	  else {
		  //cout <<"inside courier: " <<id <<endl;
	    // Request work
	    job = cardOffice->requestWork();
	    // Extract parameters from job
	    unsigned int sid = job->args.id;
	    unsigned int amount = job->args.amount;
	    WATCard* &watcard = job->args.watcard;
	    
	    // Pinter:Courier Start fund transfer
	    printer.print(Printer::Courier, id, 't', sid, amount);
	    //cout <<"about to withdraw from bank " <<endl;
	    // Transfer fond from bank
	    bank.withdraw(sid, amount);
	    //cout <<"about to deposit to watcard" <<endl;

	    // Deposit money into watcard
	    watcard->deposit(amount);

	    // Pinter:Courier Complete fund transfer
	    printer.print(Printer::Courier, id, 'T', sid, amount);

	    // Randomly lost WATCard
	    bool loseWATCard = ( mprng_(6) == 0);
	    if (loseWATCard) {
	    	//cout <<"lost watcard" <<endl;
	      Lost* lost = new Lost();
	      job->result.exception(lost);
	    } else {
	      // Deliver the real watcard pointer for the future
	      job->result.delivery(watcard);
	    }
	    delete job;
	  } // else
	} // for loop
      }
    public:
    Courier(Bank& bank, WATCardOffice* const cardOffice, Printer& printer, unsigned int id) : 
      bank(bank), cardOffice(cardOffice), printer(printer), id(id) 
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
    std::list<Job*> jobs;
  public:
    _Event Lost {};
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    ~WATCardOffice();
    FWATCard create( unsigned int sid, unsigned int amount, WATCard *&card );
    FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};


#endif // WATCARDOFFICE_H
