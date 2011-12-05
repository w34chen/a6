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

using namespace std;

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
		  cout <<"inside courier: " <<id <<endl;
	    // Request work
	    job = cardOffice->requestWork();
	    cout <<"courier requested work" <<endl;
	    // Extract parameters from job
	    unsigned int id = job->args.id;
	    unsigned int amount = job->args.amount;
	    WATCard* watcard = job->args.watcard;
	    
	    // Pinter:Courier Start fund transfer
	    printer.print(Printer::Courier, id, 't', id, amount);
	    cout <<id <<" about to withdraw from bank " <<endl;
	    // Transfer fond from bank
	    bank.withdraw(id, amount);
	    cout <<id <<" about to deposit to watcard" <<endl;
	    // Deposit money into watcard
	    watcard->deposit(amount);

	    // Pinter:Courier Complete fund transfer
	    printer.print(Printer::Courier, id, 'T', id, amount);

	    // Randomly lost WATCard
	    bool loseWATCard = ( mprng_(6) == 0);
	    if (loseWATCard) {
	    	cout <<id <<" lost watcard" <<endl;
	      Lost* lost = new Lost();
	      job->result.exception(lost);
	    }
	    cout <<id <<"about to delivery results" <<endl;
	    // Deliver the real watcard pointer for the future
	    job->result.delivery(watcard);
	    cout <<id <<"done delivery, delete job" <<endl;
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
