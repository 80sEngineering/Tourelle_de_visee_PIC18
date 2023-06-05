
#if defined(__XC)
    #include <xc.h>       
#elif defined(HI_TECH_C)
    #include <htc.h>     
#elif defined(__18CXX)
    #include <p18cxxx.h>
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        
#include <stdbool.h>       

#endif

#include "system.h"
#include "pins.h"
#include <xc.h>

void SYSTEM_Initialize(void)
{
    CLOCK_Initialize();
    PIN_MANAGER_Initialize();
    UART1_Initialize();
    PWM_Initialize();
}
