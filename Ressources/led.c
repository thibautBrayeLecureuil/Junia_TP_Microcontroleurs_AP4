#include "led.h"

void configure_LED(void){
    ANSELD = 0x00;  // TOUTES les broches du PORTD deviennent numÃ©riques
    ANSELB = 0x00;  // TOUTES les broches du PORTB deviennent numÃ©riques
    TRISD = 0x00;   //Mise Ã  0 des broches en sortie
    TRISB = 0x00;   //Mise Ã  0 des broches en sortie
    LATD = 0x01;    //On allume la première led
    LATB = 0x00;    //On eteint toutes les leds
}