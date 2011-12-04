#include <uC++.h>

#include "WATCardOffice.h"

void WATCardOffice::main() {
  /*
The WATCardOffice is an administrator task used by a student to transfer funds from its bank account to their
WATCard to buy a soda. Initially, the WATCard office creates a fixed-sized courier pool with numCouriers
courier tasks to communicate with the bank. (Additional couriers may not be created after the WATCardOffice
begins.) A student performs an asynchronous call to create to create a “real” WATCard through the output
parameter card with an initial balance. A future WATCard is returned and sufficient funds are subsequently
obtained from the bank (see Parent task) via a courier to satisfy the transfer request. A student performs an
asynchronous call to transfer when its WATCard indicates there is insufficient funds to buy a soda. A future
WATCard is returned and sufficient funds are subsequently obtained from the bank (see Parent task) via a
courier to satisfy the transfer request. The WATCard office is empowered to transfer funds from a student’s
bank-account to its WATCard by sending a request through a courier to the bank. Each courier task calls
requestWork, blocks until a Job request is ready, and then receives the next Job request as the result of the call.
As soon as the request is satisfied (i.e., money is obtained from the bank), the courier updates the student’s
WATCard. There is a 1 in 6 chance a courier loses a student’s WATCard after the update. When the card is lost,
the exception WATCardOffice::Lost is inserted into the future rather than making the future available.

   */  
  // Create fixed-sized courier pool 
  //   with numCouriers

  // Always accept create WATCard

  // Always accept transfer

  // Only accept request from courier when there is job

}

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) : 
  printer(prt), bank(bank), numCouriers(numCouriers)
{
  for (unsigned int i = 0; i < numCouriers; i ++) {
    Courier *temp = new Courier(bank, this);
    workers.push_back(temp);
  }
}
 
FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount, WATCard *&card ) {
  // Student create WATCard though output parameter card with initial balance
  // Sufficient fund is obtained from bank

  
  // Create job for this create
  Args arg;
  arg.id = sid;
  arg.amount = amount;
  arg.watcard = card;
  Job* job = new Job(arg);
  
  jobs.push(job);

// Future WATCard is returned
  return job->result;
}

FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
  // Student call to transfer when its WATCard has insufficient funds
  // Sufficient fund is obtained from bank
  

  // Create job for this transfer
  Args arg;
  arg.id = sid;
  arg.amount = amount;
  arg.watcard = card;
  Job* job = new Job(arg);
  
  jobs.push(job);

  // future WATCard is returned
  return job->result;
}
 
WATCardOffice::Job* WATCardOffice::requestWork() {
  // Courier request work
  Job* job = jobs.top();
  jobs.pop();

  return job;
}

WATCardOffice::~WATCardOffice() {
  for (unsigned int i = 0; i < numCouriers; i ++) {
    delete workers.at(i);
  }
}
