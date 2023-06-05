
#define SYS_FREQ        8000000L
#define FCY             SYS_FREQ/4
#ifndef SYSTEM_H
#define	SYSTEM_H
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "configuration_bits.h"
#include "clock.h"
#include "pins.h"
#include "uart1.h"
#include "PWM.h"

void SYSTEM_Initialize(void);

#endif	/* SYSTEM_H */