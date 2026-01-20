#include <xc.h>
#include "configbits.h"


#define _XTAL_FERQ 8000000

//Nous observons qu'avec 12k cycles nous obtenons quasiment parfaitement 10 cycles en 10 secondes
void delai_approx(void){
    unsigned long i;
    for (i=0; i<12000; i++) {
    }
}
void main(void) {
    ANSELD = 0x00;  // TOUTES les broches du PORTD deviennent numériques
    ANSELB = 0x00;  // TOUTES les broches du PORTB deviennent numériques
    TRISD = 0x00;   //Mise à 0 des broches en sortie
    TRISB = 0x00;   //Mise à 0 des broches en sortie
    LATD = 0x01;    //On allume la premi�re led
    LATB = 0x00;    //On eteint toutes les leds
    while(1) {
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
        delai_approx(); 
    }
}