#include <xc.h>
#include <math.h>
#include "configbits.h"
#include "lcd.h"
#include "spi.h"

#define _XTAL_FREQ 8000000

unsigned int offset = 0;

unsigned int encryptionStatus = 0; // 0 = chiffrement, 1 = dechiffrement

void configure_interrupt(void){
    INTCONbits.GIE = 1; // on active l'interruption globale
    INTCONbits.PEIE = 1; //on active l'interruption peripherique
}

void configure_pot(void){
    TRISAbits.TRISA0 = 1; 
    ANSELAbits.ANSA0 = 1; 
}

void configure_button(void){
    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSB0 = 0;
}

void config_adc(void){
    ADCON0bits.CHS = 0b00000; //ansel du potentiometre
    ADCON1bits.ADFM = 0; // Format : justifié à gauche
    ADCON0bits.ADON = 1; // ADC : en marche
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

/* Lecture de la valeur sur 8 bits */
char read_adc(void){
    ADCON0bits.GO = 1; // Lancer la lecture de l?ADC
    while(ADCON0bits.GO){} // Attendre la fin de l?acquisition
    return ADRESH; // Retourner les 8bits de poids fort du résultat

}

void updateDisplay(void){
    LCD_Clear();
    LCD_GoTo(0,0);
    LCD_WriteString("Offset : " + (offset));
    LCD_GoTo(1,0);
    if (encryptionStatus){
        LCD_WriteString("Dechiffrement");
    } else {
        LCD_WriteString("Chiffrement");
    }
}

void updateOffset(void){
    char res = read_adc();
    unsigned int tmp = offset;
    offset = roundf(res/7);
    
    if (tmp != offset){
        updateDisplay();
    }
}

void UART_SendChar(char dt)
{
    TX1REG = dt;
    
}

char UART_ReadChar(void)
{
    return RC1REG;
}
 
char cesar(char input){
    
    //TODO faire chiffrement
    return input + offset;
}

void __interrupt() isr(void){

    char input = UART_ReadChar();
    input = cesar();
    UART_SendChar(input);
    PIR1bits.RCIF = 0;
   
}

void main(void) {
    configure_pot();
    config_adc();
    configure_button();
    configure_interrupt();
    UART_Init();
    SPI_InitializePins();
    LCD_InitializePins();
    SPI_Initialize();
    LCD_Initialize();
    
    while(1){
        if (!PORTBbits.RB0) {
            if (encryptionStatus){
                encryptionStatus = 0;
            } else {
                encryptionStatus = 1;
            }
            updateDisplay();
        } 
        updateOffset();
    }
}