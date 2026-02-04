#include <xc.h>
#include "configbits.h"

#define _XTAL_FREQ 8000000

void UART_SendChar(char dt)
{
    TX1REG = dt;
    
}

char UART_ReadChar()
{
    return RC1REG;
}
 
void __interrupt() isr(void){

    char input = UART_ReadChar();
    UART_SendChar(input);
    PIR1bits.RCIF = 0;
   
}

void configure_interrupt(void){
    INTCONbits.GIE = 1; // on active l'interruption globale
    INTCONbits.PEIE = 1; //on active l'interruption peripherique
}

void UART_Init(void)
{
    /* setup UART at 9600 baud */
    PIE1bits.TXIE = 0;                      /* disable UART interrupts */
    PIE1bits.RCIE = 1;
    RC1STA = 0;                             /* turn off UART RX */
    TX1STA = 0;                             /* turn off UART TX*/
    RXPPS  = 0b10111;                       /* Assign RC7 to UART RX*/
    RC6PPS = 0b10100;                       /* Assign UART TX to RC6*/
 
    TRISCbits.TRISC6 = 0;                             /* sets UART TX pin RC6 as an output*/
    LATCbits.LATC6  = 1;                             /* Set UART TX ouput high*/
    
    ANSELCbits.ANSC7 = 0;
    TRISCbits.TRISC7 = 1;                            /* Set for high frequency output*/
    
    TX1STAbits.SYNC = 0;
    TX1STAbits.BRGH = 0;                               /* setting up the baud rate generator*/
    BAUD1CONbits.BRG16 = 0;
    
    SP1BRGL = 12;
    SP1BRGH = 0;
    
    RC1STAbits.SPEN = 1; 
    TX1STAbits.TXEN = 1;
    RC1STAbits.CREN = 1;                              /* enables transmission */

}

void main(void) {
    UART_Init();
    configure_interrupt();

    while(1){
    }
}