/*
 * mprng.h
 *
 *  Created on: 2011-12-02
 *      Author: Jenny
 */

#ifndef MPRNG_H_
#define MPRNG_H_

#include "uC++.h"
#include "PRNG.h"

_Monitor MPRNG: private PRNG {
public:
// wrapper members for PRNG members making them mutex
	MPRNG( unsigned int seed = 1009 ) { srand( seed ); }
	void seed( unsigned int seed ) { srand( seed ); }
    unsigned int operator()() { return rand(); }
    unsigned int operator()(unsigned int x1) { return PRNG::operator()(x1);}
    unsigned int operator()(unsigned int x2, unsigned int x1) { return PRNG::operator()(x2, x1);}
};

#endif /* MPRNG_H_ */
