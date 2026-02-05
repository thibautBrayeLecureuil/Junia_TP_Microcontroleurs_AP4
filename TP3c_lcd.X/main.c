#include <xc.h>
#include "configbits.h"
#include "lcd.h"
#include "spi.h"

#define _XTAL_FREQ 8000000

void main(void) {
    SPI_InitializePins();
    LCD_InitializePins();
    SPI_Initialize();
    LCD_Initialize();
    LCD_Clear();
    LCD_GoTo(0,0);
    LCD_WriteString("#saucisse");
    LCD_GoTo(1,0);
    LCD_WriteString("#merguez"); 
    while(1){
    }
}