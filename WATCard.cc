#include <uC++.h>

#include "WATCard.h"

WATCard::WATCard( const WATCard & ) {
}

WATCard WATCard::&operator=( const WATCard & ) {
}

WATCard::WATCard() {
  balance = 0;
}

void WATCard::deposit( unsigned int amount ) {
  // use courier to deposit
}

void WATCard::withdraw( unsigned int amount ) {
  
}

unsigned int WATCard::getBalance() {

}
