#ifndef UART_INTERFACE_H
#define	UART_INTERFACE_H

#include <stdbool.h>
#include <stdint.h>
#include <xc.h>
    

struct UART_INTERFACE
{   
    void (*Initialize)(void);
    uint8_t (*Read)(void);
    void (*Write)(uint8_t);
    void (*RxCompleteCallbackRegister)(void (*CallbackHandler)(void));
    void (*TxCompleteCallbackRegister)(void (*CallbackHandler)(void));
    void (*ErrorCallbackRegister)(void (*CallbackHandler)(void));
    void (*FramingErrorCallbackRegister)(void (*CallbackHandler)(void));
    void (*OverrunErrorCallbackRegister)(void (*CallbackHandler)(void));
    void (*ParityErrorCallbackRegister)(void (*CallbackHandler));
    void (*ChecksumErrorCallbackRegister)(void (*CallbackHandler));
    bool (*IsRxReady)(void);
    bool (*IsTxReady)(void);
    bool (*IsTxDone)(void);
};

#endif	/* UART_INTERFACE_H */

