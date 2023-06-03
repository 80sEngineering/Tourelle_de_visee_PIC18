#ifndef UART1_H
#define	UART1_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include "uart_interface.h"


#define UART1_isDataReady  (UART1_IsRxReady())
extern const struct UART_INTERFACE UART1_Interface;

typedef union {
    struct {
        unsigned perr : 1;
        unsigned ferr : 1;
        unsigned oerr : 1;
        unsigned reserved : 5;
    };
    uint8_t status;
}uart1_status_t;


bool __attribute__(( deprecated )) UART1_is_tx_ready(void);
bool __attribute__(( deprecated )) UART1_is_rx_ready(void);
bool __attribute__(( deprecated )) UART1_is_tx_done(void);
uart1_status_t __attribute__(( deprecated )) UART1_get_last_status(void);


void UART1_Initialize(void);


bool UART1_IsRxReady(void);


bool UART1_IsTxReady(void);


bool UART1_IsTxDone(void);


uart1_status_t UART1_GetLastStatus(void);


uint8_t UART1_Read(void);
 
void UART1_Write(uint8_t txData);

void UART1_sendString(const char *str);
 
void UART1_Transmit_ISR(void);

    
void UART1_Receive_ISR(void);


void UART1_RxDataHandler(void);


void UART1_SetFramingErrorHandler(void (* interruptHandler)(void));


void UART1_SetOverrunErrorHandler(void (* interruptHandler)(void));


void UART1_SetErrorHandler(void (* interruptHandler)(void));


void UART1_FramingError_ISR(void);


void UART1_UartInterrupt_ISR(void);


void (*UART1_RxInterruptHandler)(void);


void (*UART1_TxInterruptHandler)(void);


void (*UART1_FramingErrorInterruptHandler)(void);


void (*UART1_UARTInterruptHandler)(void);


void UART1_SetRxInterruptHandler(void (* InterruptHandler)(void));


void UART1_SetTxInterruptHandler(void (* InterruptHandler)(void));


void UART1_SetFramingErrorInterruptHandler(void (* InterruptHandler)(void));


void UART1_SetUartInterruptHandler(void (* InterruptHandler)(void));



#endif	/* UART1_H */

