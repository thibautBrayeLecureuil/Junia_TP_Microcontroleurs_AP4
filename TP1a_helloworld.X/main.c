#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC


#define _XTAL_FREQ 32000000

void main(void) {
    /* Code d'initialisation */
    TRISD = 0x00;
    ANSELD = 0x00;
    LATD = 0x00;

    while(1){
        /* Code a executer dans une boucle infinie */
        
        LATD = 0x0F;
        __delay_ms(500);
        LATD = 0xF0;
        __delay_ms(500);
    }
}
