#include <uC++.h>
#include <iostream>

#include "WATCardOffice.h"

void WATCardOffice::main() {
  // Printer: WATCardOffice Start
  printer.print(Printer::WATCardOffice, 'S');

  for (;;) {
    _Accept(~WATCardOffice) {
      break;
    }
    // Always accept create WATCard
    // Always accept transfer
    or _Accept(create) {
      // Printer::Creation Complete
      printer.print(Printer::WATCardOffice, 'C', jobs.front()->args.id, jobs.front()->args.amount);
    }
    or _Accept(transfer) {
      // Printer::Transfer Complete
      printer.print(Printer::WATCardOffice, 'T', jobs.front()->args.id, jobs.front()->args.amount);
    }
    or _When (!jobs.empty()) _Accept (requestWork) {
      // Only accept request from courier when there is job
      // Printer::Courier Complete
      printer.print(Printer::WATCardOffice, 'W');
    } 
  }
  
  for (unsigned int i = 0; i < numCouriers ; i++) {
    _Accept(requestWork);
  }
  // Printer: WATCardOffice Finish
  printer.print(Printer::WATCardOffice, 'F');

}

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) : 
  printer(prt), bank(bank), numCouriers(numCouriers)
{
  // Create fixed-sized courier pool 
  //   with numCouriers
  for (unsigned int i = 0; i < numCouriers; i ++) {
    Courier *temp = new Courier(bank, this, printer, i);
    workers.push_back(temp);
  }
}
 
FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount, WATCard *&card ) {
  // Student create WATCard though output parameter card with initial balance
  card = new WATCard();

  // Create job for this create
  Args arg(sid, amount, card);
  Job* job = new Job(arg);

  jobs.push_back(job);
  // Future WATCard is returned
  return job->result;
}

FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
  // Student call to transfer when its WATCard has insufficient funds
  // Sufficient fund is obtained from bank

  // Create job for this transfer
  Args arg(sid, amount, card);
  Job* job = new Job(arg);
  
  jobs.push_back(job);
  // future WATCard is returned
  return job->result;
}
 
WATCardOffice::Job* WATCardOffice::requestWork() {
  // Courier request work
  Job* job;
  if (!jobs.empty()) {
    job = jobs.front();
    jobs.pop_front();
  } else {
    job = NULL;
  }
  
  return job;
}

WATCardOffice::~WATCardOffice() {
  for (unsigned int i = 0; i < numCouriers; i ++) {
    delete workers.at(i);
  }
}
