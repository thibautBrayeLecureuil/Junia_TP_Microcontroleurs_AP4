#include <xc.h>
#include "configbits.h"


#define _XTAL_FERQ 8000000

void init_PWM4(void) {
    
    PWM4DCH = 0; // poids fort : 0
    PWM4DCL = 0; // poids faible : 0
    
    PWM4CONbits.PWM4EN = 1;
  
}

void configure_pot(void){
    TRISAbits.TRISA0 = 1; 
    ANSELAbits.ANSA0 = 1; 
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

/* Configurer l?ADC pour lire la température interne */
void config_adc(void){
 ADCON0bits.CHS = 0b00000; // Entrée : capteur de température
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
    init_PWM4();
    configure_scaler();
    while(1) {
        PWM4DCH = read_adc();
    }
}