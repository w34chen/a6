#ifndef WATCARDOFFICE_H
#define WATCARDOFFICE_H

#include <uC++.h>
#include <vector>
#include <stack>

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
      Job* job;
      void main() {
	// Request work
	job = cardOffice->requestWork();
	
	// Extract parameters from job
	unsigned int id = job->args.id;
	unsigned int amount = job->args.amount;
	WATCard* watcard = job->args.watcard;

	// Transfer fond from bank
	bank.withdraw(id, amount);
	
	// Deposit money into watcard
	watcard->deposit(amount);
	
	// Randomly lost WATCard
	bool loseWATCard = ( mprng_(6) == 0);
	if (loseWATCard) {
	  Lost* lost = new Lost();
	  job->result.exception(lost);
	}
	
	// Deliver the real watcard pointer for the future
	job->result.delivery(watcard);

	delete job;
      }
    public:
    Courier(Bank& bank, WATCardOffice* const cardOffice) : bank(bank), cardOffice(cardOffice) {
	job = NULL;
      }
      
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
