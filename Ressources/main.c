#include <xc.h>
#include "configbits.h"
#include "time.h"
#include "led.h"
#include "interrupt.h"


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

void main(void) {
    configure_LED();
    configure_interrupt();
    configure_scaler();
    
    while(1) {
        /*
        
         */
    }
}