#include "pins.h"

void PIN_MANAGER_Initialize(void)
{
    TRISFbits.TRISF4 = 0;
    TRISFbits.TRISF5 = 0;
    TRISFbits.TRISF6 = 0;
    TRISFbits.TRISF7 = 0;
    PORTFbits.RF4 = 0;
    PORTFbits.RF5 = 0;
    PORTFbits.RF6 = 0;
    PORTFbits.RF7 = 0;
    
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

