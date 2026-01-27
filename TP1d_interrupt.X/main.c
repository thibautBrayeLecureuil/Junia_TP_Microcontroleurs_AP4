#include <xc.h>
#include "configbits.h"


#define _XTAL_FERQ 8000000


unsigned int compteur = 0;

void __interrupt() isr(void){
    
    PIR1bits.TMR2IF = 0;
    
    if( compteur == 125){ // on compte j'usqu'� 125 car l'interuption a lieu tout les 1 ms
        compteur = 0;
        if (LATD == 0x08){ // on change de registre quand on arrive au bout des leds
                LATD = 0x00;
                LATB = 0x01;
            }
            else if (LATB == 0x08){ // on change de registre quand on arrive au bout des leds
                LATB = 0x00;
                LATD = 0x01;
            }else if (LATB != 0x00) {
                LATB = LATB << 1; //On decale les bits vers la droite
            } else {
                LATD = LATD << 1; //On decale les bits vers la droite
            }
    }else{
        compteur = compteur + 1;
    }
}

void configure_interrupt(void){
    
    INTCONbits.GIE = 1; // on active l'interruption globale
    INTCONbits.PEIE = 1; //on active l'interruption peripherique
    PIE1bits.TMR2IE = 1; //on active l'interruption sur le timer2

    
}

void configure_scaler(void){
    
    INTCONbits.GIE = 1; // on active l'interruption globale
    INTCONbits.PEIE = 1; //on active l'interruption peripherique
    PIE1bits.TMR2IE = 1; //on active l'interruption sur le timer2
    T2CONbits.TMR2ON = 1; //on active le timer2
    T2CONbits.T2OUTPS0 = 1; // mettre le postscaler sur 2
    T2CONbits.T2CKPS0 = 1; // mettre le prescaler sur 4

    PR2 = 249;
    
}


void main(void) {
    ANSELD = 0x00;  // TOUTES les broches du PORTD deviennent numériques
    ANSELB = 0x00;  // TOUTES les broches du PORTB deviennent numériques
    TRISD = 0x00;   //Mise à 0 des broches en sortie
    TRISB = 0x00;   //Mise à 0 des broches en sortie
    LATD = 0x01;    //On allume la premi�re led
    LATB = 0x00;    //On eteint toutes les leds
    
    configure_interrupt();
    configure_scaler();
    
    while(1) {
        /*
        
         */
    }
}