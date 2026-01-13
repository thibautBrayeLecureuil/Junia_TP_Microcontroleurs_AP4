#include <xc.h>
#include "configbits.h"
//Avec 60k cycles nous etions à 13 secondes au bout de 10 cycles
//Nous observons qu'avec 48k cycles nous obtenons quasiment parfaitement 10 cycles en 10 secondes
void delai_approx(void){
    unsigned long i;
    for (i=0; i<48000; i++) {
    }
}
void main(void) {
    ANSELD = 0x00;  // TOUTES les broches du PORTD deviennent numériques
    ANSELB = 0x00;  // TOUTES les broches du PORTB deviennent numériques
    TRISD = 0x00;   //Mise à 0 des broches en sortie
    TRISB = 0x00;   //Mise à 0 des broches en sortie
    LATD = 0x00;    //Mise à 0 des bropches en sortie
    LATB = 0x00;    //Mise à 0 des bropches en sortie

    while(1) {
        LATD = 0x0F; // D1-D4 allumées
        LATB = 0x00; // D5-D8 éteintes
        delai_approx();

        LATD = 0x00; // D1-D4 éteintes
        LATB = 0x0F; // D5-D8 allumées
        delai_approx();
    }
}
