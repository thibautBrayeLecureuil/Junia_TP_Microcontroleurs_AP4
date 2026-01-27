#include <xc.h>
#include "configbits.h"


#define _XTAL_FERQ 8000000

unsigned int compteur = 0;


void configure_pot(void){
    TRISAbits.TRISA0 = 1; 
    ANSELAbits.ANSA0 = 1; 
}

void configure_LED(void){
    TRISD = 0x00;   //Mise ÃƒÂ  0 des broches en sortie
    TRISB = 0x00;   //Mise ÃƒÂ  0 des broches en sortie
    LATD = 0x00;    //On eteint toutes les leds
    LATB = 0x00;    //On eteint toutes les leds
}

/* Configurer l?ADC pour lire la température interne */
void config_adc(void){
    ADCON0bits.CHS = 0b00000; //ansel du potentiometre
    ADCON1bits.ADFM = 0; // Format : justifié à gauche
    ADCON0bits.ADON = 1; // ADC : en marche
}
/* Lecture de la valeur sur 8 bits */
char read_adc(void){
    ADCON0bits.GO = 1; // Lancer la lecture de l?ADC
    while(ADCON0bits.GO){} // Attendre la fin de l?acquisition
    return ADRESH; // Retourner les 8bits de poids fort du résultat

}

void main(void) {
    char res;
    config_adc();
    configure_LED();
    configure_pot();
    while(1) {
        res = read_adc();
        if ( res < 32 ){
            LATD = 0x01;
            LATB = 0x00;
        } else if (res < 64 ){
            LATD = 0x02;
            LATB = 0x00;
        } else if (res < 96 ){
            LATD = 0x04;
            LATB = 0x00;
        } else if (res < 128 ){
            LATD = 0x08;
            LATB = 0x00;
        } else if (res < 160 ){
            LATB = 0x01;
            LATD = 0x00;
        } else if (res < 192 ){
            LATB = 0x02;
            LATD = 0x00;
        } else if (res < 224 ){
            LATB = 0x04;
            LATD = 0x00;
        } else{
            LATB = 0x08;
            LATD = 0x00;
        }
        
    }
}