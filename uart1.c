#include <xc.h>
#include "uart1.h"

const struct UART_INTERFACE UART1_Interface = {
  .Initialize = UART1_Initialize,
  .Write = UART1_Write,
  .Read = UART1_Read,
  .RxCompleteCallbackRegister = NULL,
  .TxCompleteCallbackRegister = NULL,
  .ErrorCallbackRegister = UART1_SetErrorHandler,
  .FramingErrorCallbackRegister = UART1_SetFramingErrorHandler,
  .OverrunErrorCallbackRegister = UART1_SetOverrunErrorHandler,
  .ParityErrorCallbackRegister = NULL,
  .ChecksumErrorCallbackRegister = NULL,
  .IsRxReady = UART1_IsRxReady,
  .IsTxReady = UART1_IsTxReady,
  .IsTxDone = UART1_IsTxDone
};

/**
  Section: Macro Declarations
*/
#define UART1_TX_BUFFER_SIZE 8
#define UART1_RX_BUFFER_SIZE 8

/**
  Section: Global Variables
*/

static volatile uint8_t uart1TxHead = 0;
static volatile uint8_t uart1TxTail = 0;
static volatile uint8_t uart1TxBuffer[UART1_TX_BUFFER_SIZE];
volatile uint8_t uart1TxBufferRemaining;

static volatile uint8_t uart1RxHead = 0;
static volatile uint8_t uart1RxTail = 0;
static volatile uint8_t uart1RxBuffer[UART1_RX_BUFFER_SIZE];
static volatile uart1_status_t uart1RxStatusBuffer[UART1_RX_BUFFER_SIZE];
volatile uint8_t uart1RxCount;
static volatile uart1_status_t uart1RxLastError;

/**
  Section: UART1 APIs
*/
void (*UART1_FramingErrorHandler)(void);
void (*UART1_OverrunErrorHandler)(void);
void (*UART1_ErrorHandler)(void);

void UART1_DefaultFramingErrorHandler(void);
void UART1_DefaultOverrunErrorHandler(void);
void UART1_DefaultErrorHandler(void);

void UART1_Initialize(void)
{
    
    // Disable interrupts before changing states
    PIE4bits.U1RXIE = 0;
    UART1_SetRxInterruptHandler(UART1_Receive_ISR);
    PIE4bits.U1TXIE = 0;
    UART1_SetTxInterruptHandler(UART1_Transmit_ISR);
    PIE4bits.U1EIE = 0;
    UART1_SetFramingErrorInterruptHandler(UART1_FramingError_ISR);
    PIE4bits.U1IE = 0;
    UART1_SetUartInterruptHandler(UART1_UartInterrupt_ISR);
    
   
    U1CON0bits.BRGS = 1;
    U1CON0bits.ABDEN = 0;
    U1CON0bits.TXEN = 1;
    U1CON0bits.RXEN = 1;
    U1CON0bits.MODE = 0b0000;
    U1BRG = 0x19;

    U1CON1bits.ON = 1;
    UART1_SetFramingErrorHandler(UART1_DefaultFramingErrorHandler);
    UART1_SetOverrunErrorHandler(UART1_DefaultOverrunErrorHandler);
    UART1_SetErrorHandler(UART1_DefaultErrorHandler);

    uart1RxLastError.status = 0;

}

bool UART1_IsRxReady(void)
{
    return (bool)(PIR4bits.U1RXIF);
}

bool UART1_is_rx_ready(void)
{    
    return UART1_IsRxReady();
}

bool UART1_IsTxReady(void)
{
    return (bool)(PIR4bits.U1TXIF && U1CON0bits.TXEN);
}

bool UART1_is_tx_ready(void)
{
    return UART1_IsTxReady();
}

bool UART1_IsTxDone(void)
{
    return U1ERRIRbits.TXMTIF;
}

bool UART1_is_tx_done(void)
{
    return UART1_IsTxDone();
}

uart1_status_t UART1_GetLastStatus(void){
    return uart1RxLastError;
}

uart1_status_t UART1_get_last_status(void){
    return UART1_GetLastStatus();
}


uint8_t UART1_Read(void)
{
    while(!PIR4bits.U1RXIF)
    {
    }

    uart1RxLastError.status = 0;

    if(U1ERRIRbits.FERIF){
        uart1RxLastError.ferr = 1;
        UART1_FramingErrorHandler();
    }

    if(U1ERRIRbits.RXFOIF){
        uart1RxLastError.oerr = 1;
        UART1_OverrunErrorHandler();
    }

    if(uart1RxLastError.status){
        UART1_ErrorHandler();
    }

    return U1RXB;
}


void UART1_Write(uint8_t txData)
{

    U1TXB = txData;    // Write the data byte to the USART.
}

void UART1_sendString(const char *str)
{
    while(*str)
    {
        while (!(UART1_IsTxReady()));
        UART1_Write(*str++);
    }
}

void UART1_Transmit_ISR(void)
{
    // use this default transmit interrupt handler code
    if(sizeof(uart1TxBuffer) > uart1TxBufferRemaining)
    {
        U1TXB = uart1TxBuffer[uart1TxTail++];
       if(sizeof(uart1TxBuffer) <= uart1TxTail)
        {
            uart1TxTail = 0;
        }
        uart1TxBufferRemaining++;
    }
    else
    {
        PIE4bits.U1TXIE = 0;
    }
    
    // or set custom function using UART1_SetTxInterruptHandler()
}

void UART1_Receive_ISR(void)
{
    // use this default receive interrupt handler code
    uart1RxStatusBuffer[uart1RxHead].status = 0;

    if(U1ERRIRbits.FERIF){
        uart1RxStatusBuffer[uart1RxHead].ferr = 1;
        UART1_FramingErrorHandler();
    }
    
    if(U1ERRIRbits.RXFOIF){
        uart1RxStatusBuffer[uart1RxHead].oerr = 1;
        UART1_OverrunErrorHandler();
    }
    
    if(uart1RxStatusBuffer[uart1RxHead].status){
        UART1_ErrorHandler();
    } else {
        UART1_RxDataHandler();
    }

    // or set custom function using UART1_SetRxInterruptHandler()
}

void UART1_RxDataHandler(void){
    // use this default receive interrupt handler code
    uart1RxBuffer[uart1RxHead++] = U1RXB;
    if(sizeof(uart1RxBuffer) <= uart1RxHead)
    {
        uart1RxHead = 0;
    }
    uart1RxCount++;
}

void UART1_DefaultFramingErrorHandler(void){}

void UART1_DefaultOverrunErrorHandler(void){}

void UART1_DefaultErrorHandler(void){
}

void UART1_SetFramingErrorHandler(void (* interruptHandler)(void)){
    UART1_FramingErrorHandler = interruptHandler;
}

void UART1_SetOverrunErrorHandler(void (* interruptHandler)(void)){
    UART1_OverrunErrorHandler = interruptHandler;
}

void UART1_SetErrorHandler(void (* interruptHandler)(void)){
    UART1_ErrorHandler = interruptHandler;
}

void UART1_FramingError_ISR(void)
{
    // To clear the interrupt condition, all bits in the UxERRIR register must be cleared
    U1ERRIR = 0;
    
    // add your UART1 error interrupt custom code

}

void UART1_UartInterrupt_ISR(void)
{
    // WUIF must be cleared by software to clear UxIF
    U1UIRbits.WUIF = 0;
    
    
    // add your UART1 interrupt custom code
}

void UART1_SetRxInterruptHandler(void (* InterruptHandler)(void)){
    UART1_RxInterruptHandler = InterruptHandler;
}

void UART1_SetTxInterruptHandler(void (* InterruptHandler)(void)){
    UART1_TxInterruptHandler = InterruptHandler;
}

void UART1_SetFramingErrorInterruptHandler(void (* InterruptHandler)(void)){
    UART1_FramingErrorInterruptHandler = InterruptHandler;
}

void UART1_SetUartInterruptHandler(void (* InterruptHandler)(void)){
    UART1_UARTInterruptHandler = InterruptHandler;
}

