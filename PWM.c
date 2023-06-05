#include <xc.h>
#include "clock.h"
void PWM_Initialize(void)
{
    TRISCbits.TRISC1 = 0;
}

void PWM_value_send(int value)
{
    LATCbits.LATC1 = 1;
    __delay_us(2000);
    LATCbits.LATC1 = 0;
    __delay_us(18000);
    
}
