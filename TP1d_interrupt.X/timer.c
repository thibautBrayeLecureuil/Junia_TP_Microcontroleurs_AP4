#include "timer.h"

void configure_scaler(void){

    T2CONbits.TMR2ON = 1; //on active le timer2
    T2CONbits.T2OUTPS0 = 1; // mettre le postscaler sur 2
    T2CONbits.T2CKPS0 = 1; // mettre le prescaler sur 4

    PR2 = 249;
    
}