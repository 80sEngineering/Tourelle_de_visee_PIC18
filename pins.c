#include "pins.h"

void PIN_MANAGER_Initialize(void)
{
    TRISCbits.TRISC7 = 1; //Input
    TRISFbits.TRISF7 = 0; //Output
    ANSELCbits.ANSELC7 = 0;
    ANSELFbits.ANSELF7 = 1;
    U1RXPPS = 0x17; //RC7->UART1:U1RX;
    RF0PPS = 0x20;  //RF0->UART1:TX1;
}
  
void PIN_MANAGER_IOC(void)
{
}

