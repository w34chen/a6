#ifndef WATCARD_H
#define WATCARD_H

#include <uC++.h>
#include <uFuture.h>

class WATCard {
    WATCard( const WATCard & );			// prevent copying
    WATCard &operator=( const WATCard & );
    unsigned int balance;
  public:
    WATCard();
    void deposit( unsigned int amount );
    void withdraw( unsigned int amount );
    unsigned int getBalance();
};

typedef Future_ISM<WATCard *> FWATCard;		// future WATCard pointer


#endif // WATCARD_H
