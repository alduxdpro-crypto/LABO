/* Ejemplo de uso: PIC18F4550 + LCD 16x2, XC8.
   Ajustar el oscilador y los CONFIG bits del proyecto para 8 MHz reales. */
#define _XTAL_FREQ 8000000UL
#include <xc.h>
#include "lcd.h"

void main(void)
{
    LCD_Init();
    LCD_Pos(1, 1);
    LCD_Texto("SISTEMA PIC18");
    LCD_Pos(2, 1);
    LCD_Texto("UNIDADES: ");
    LCD_Numero3(12);
    while (1) { }
}
