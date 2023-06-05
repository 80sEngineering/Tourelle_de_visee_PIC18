#ifndef PINS_H
#define	PINS_H

#include <xc.h>

#define STEP1 LATFbits.LATF4
#define STEP2 LATFbits.LATF5
#define STEP3 LATFbits.LATF6
#define STEP4 LATFbits.LATF7

void PIN_MANAGER_Initialize(void);


void PIN_MANAGER_IOC(void);




#endif	/* PINS_H */

