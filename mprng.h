/*
 * mprng.h
 *
 *  Created on: 2011-12-02
 *      Author: Jenny
 */

#ifndef MPRNG_H_
#define MPRNG_H_

#include "uC++.h"

_Monitor MPRNG: private PRNG {
public:
// wrapper members for PRNG members making them mutex
	MPRNG( unsigned int seed = 1009 ) { srand( seed ); }
	void seed( unsigned int seed ) { srand( seed ); }
    unsigned int operator()() { return rand(); }
};

#endif /* MPRNG_H_ */