#include "interrupt.h"
#include <xc.h>
void configure_interrupt(void){
    
    INTCONbits.GIE = 1; // on active l'interruption globale
    INTCONbits.PEIE = 1; //on active l'interruption peripherique
    PIE1bits.TMR2IE = 1; //on active l'interruption sur le timer2
    
}