#include <xc.h>
#include "configbits.h"


#define _XTAL_FERQ 8000000

unsigned int compteur = 0;
unsigned int isPositive = 1;

void configure_interrupt(void){
    INTCONbits.GIE = 1; // on active l'interruption globale
    INTCONbits.PEIE = 1; //on active l'interruption peripherique
    PIE1bits.TMR2IE = 1; //on active l'interruption sur le timer2
}

void configure_scaler(void){

    T2CONbits.TMR2ON = 1; //on active le timer2
    T2CONbits.T2OUTPS0 = 1; // mettre le postscaler sur 4
    T2CONbits.T2CKPS1 = 1; // mettre le prescaler sur 3

    PR2 = 249;
    
}

void init_PWM4(void) {
    
    PWM4DCH = 0; // poids fort : 0
    PWM4DCL = 0; // poids faible : 0
    
    PWM4CONbits.PWM4EN = 1;
  
}

void configure_LED(void){
    TRISDbits.TRISD0 = 0;
    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSB0 = 0; 
    RD0PPS = 0x0F;

}


void __interrupt() isr(void){
    
    PIR1bits.TMR2IF = 0;
    
    if (isPositive == 1){
        if( compteur == 255){
            isPositive = 0;
            compteur --;
        } else {
            compteur ++;
        }
    } else {
        if( compteur == 0){
            isPositive = 1;
            compteur ++;
        } else {
            compteur --;
        }
    }
    PWM4DCH = compteur;
}

void main(void) {
    init_PWM4();
    configure_LED();
    configure_interrupt();
    configure_scaler();
    while(1) {
    }
}