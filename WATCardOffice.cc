#include <uC++.h>
#include <iostream>

#include "WATCardOffice.h"

using namespace std;

void WATCardOffice::main() {
  // Printer: WATCardOffice Start
  printer.print(Printer::WATCardOffice, 'S');

  for (;;) {
    // Always accept create WATCard
    // Always accept transfer
    _Accept(create) {
      // Printer::Creation Complete
      printer.print(Printer::WATCardOffice, 'C', jobs.top()->args.id, jobs.top()->args.amount);
    }
    or _Accept(transfer) {
      // Printer::Transfer Complete
      printer.print(Printer::WATCardOffice, 'T', jobs.top()->args.id, jobs.top()->args.amount);
    }
    or _When (jobs.size() != 0) _Accept (requestWork) {
      // Only accept request from courier when there is job
      // Printer::Courier Complete
      printer.print(Printer::WATCardOffice, 'W');
    } 
  }
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
  
  // Create job for this create
  Args arg(sid, amount, card, true);
  Job* job = new Job(arg);
  
  jobs.push(job);

  // Future WATCard is returned
  return job->result;
}

FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
  // Student call to transfer when its WATCard has insufficient funds

  // Create job for this transfer
  Args arg(sid, amount, card, false);
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
