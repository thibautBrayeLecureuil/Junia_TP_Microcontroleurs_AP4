#include <xc.h>
#include "configbits.h"


#define _XTAL_FREQ 8000000

//compteur pour l'intensité
unsigned int compteur = 0;

//booleen pour connaitre le sens de l'incrementation
unsigned int isPositive = 1;

void configure_interrupt(void){
    INTCONbits.GIE = 1; // on active l'interruption globale
    INTCONbits.PEIE = 1; //on active l'interruption peripherique
    PIE1bits.TMR2IE = 1; //on active l'interruption sur le timer2
}

void configure_scaler(void){
    
    //L'intensité va de 0 à 255
    //On veut qu'une montée ou une descente dure 1 seconde.
    //1/255 = 0,0039206 secondes
    //Avec ces valeurs de PR2, postcaler et prescaler nous avons 0.0039204 secondes

    T2CONbits.TMR2ON = 1; //on active le timer2
    
    T2CONbits.T2OUTPS0 = 1; // mettre le postscaler sur 2
    T2CONbits.T2CKPS1 = 1; // mettre le prescaler sur 16

    PR2 = 243;
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
    
    //On incremente
    if (isPositive == 1){
        //L'intensité et au maximum
        if( compteur == 255){
            isPositive = 0;
            compteur --;
        } else {
            compteur ++;
        }
    //On decremente
    } else {
        //L'intensité et au minimum
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