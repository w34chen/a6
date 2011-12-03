#include <uC++.h>

#include "WATCardOffice.h"

void WATCardOffice::main() {
  
}

_Event WATCardOffice::Lost {
  // This is exception where the WATCard is lost

}

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) : 
  printer(prt), bank(bank), numCouriers(numCouriers)
{
  for (int i = 0; i < numCouriers; i ++) {
    Courier *temp = new Courier();
    workers.push_back(temp);
  }
}
 
FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount, WATCard *&card ) {

}

FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {

}
 
Job* WATCardOffice::requestWork() {

}

WATCardOffice::~WATCardOffice() {
  for (int i = 0; i < numCouriers; i ++) {
    delete workers.at(i);
  }
}
