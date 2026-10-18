#ifndef LCD_H
#define LCD_H

#include <xc.h>

/* LCD HD44780 16x2, 4 bits, PIC18F4550, XC8.
   RS=RD0, E=RD1, D4=RD4, D5=RD5, D6=RD6, D7=RD7.
   RW=GND. PORTD is reserved for the LCD.
   Define _XTAL_FREQ in the project (e.g. 8000000UL).
   Configure the actual oscillator and configuration bits separately. */

#ifndef _XTAL_FREQ
#error "Define _XTAL_FREQ in project options or before including lcd.h (e.g. 8000000UL)"
#endif

void LCD_Init(void);
void LCD_Cmd(unsigned char cmd);
void LCD_Char(char c);
void LCD_Texto(const char *texto);
void LCD_Pos(unsigned char fila, unsigned char columna);
void LCD_Numero3(unsigned int numero);
void LCD_Limpiar(void);

#endif
