#include <xc.h>
#include "configbits.h" 

#define _XTAL_FREQ 8000000

void init_PWM4(void) {
    
    PWM4DCH = 0; // poids fort : 0
    PWM4DCL = 0; // poids faible : 0
    
    PWM4CONbits.PWM4EN = 1;
  
}

void configure_scaler(void){

    T2CONbits.TMR2ON = 1; //on active le timer2
    T2CONbits.T2OUTPS0 = 4; // mettre le postscaler sur 4
    T2CONbits.T2CKPS0 = 3; // mettre le prescaler sur 3

    PR2 = 249;
    
}

void configure_LED(void){
    TRISDbits.TRISD0 = 0;
    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSB0 = 0; 
    RD0PPS = 0x0F;

}

void main(void) {

    // Initialisations
    init_PWM4();
    configure_LED();
    configure_scaler();

    while(1) {

        if (PORTBbits.RB0 == 0) {

            PWM4DCH = 254; 
        } 
        else {
            PWM4DCH = 25;   

        }
    }
}