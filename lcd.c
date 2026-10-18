#include "lcd.h"

#define LCD_RS LATDbits.LATD0
#define LCD_E  LATDbits.LATD1

static void lcd_pulso(void)
{
    LCD_E = 1;
    __delay_us(2);
    LCD_E = 0;
    __delay_us(50);
}

static void lcd_nibble(unsigned char n)
{
    LATD = (LATD & 0x0F) | ((n & 0x0F) << 4);
    lcd_pulso();
}

static void lcd_byte(unsigned char valor, unsigned char rs)
{
    LCD_RS = rs;
    lcd_nibble(valor >> 4);
    lcd_nibble(valor);
}

void LCD_Cmd(unsigned char cmd)
{
    lcd_byte(cmd, 0);
    if (cmd == 0x01 || cmd == 0x02)
        __delay_ms(2);
}

void LCD_Char(char c)
{
    lcd_byte((unsigned char)c, 1);
}

void LCD_Init(void)
{
    LATD = 0x00;
    TRISD = 0x00;
    __delay_ms(40);
    LCD_RS = 0;
    lcd_nibble(0x03);
    __delay_ms(5);
    lcd_nibble(0x03);
    __delay_us(150);
    lcd_nibble(0x03);
    __delay_us(150);
    lcd_nibble(0x02);
    LCD_Cmd(0x28); /* 4 bits, 2 lines, 5x8 */
    LCD_Cmd(0x08); /* Display off */
    LCD_Cmd(0x01); /* Clear */
    LCD_Cmd(0x06); /* Entry mode */
    LCD_Cmd(0x0C); /* Display on, cursor off */
}

void LCD_Texto(const char *texto)
{
    while (*texto != '\0')
        LCD_Char(*texto++);
}

void LCD_Pos(unsigned char fila, unsigned char columna)
{
    if (fila < 1 || fila > 2 || columna < 1 || columna > 16)
        return;
    LCD_Cmd((fila == 1 ? 0x80 : 0xC0) + columna - 1);
}

void LCD_Numero3(unsigned int numero)
{
    numero %= 1000;
    LCD_Char('0' + (numero / 100));
    LCD_Char('0' + ((numero / 10) % 10));
    LCD_Char('0' + (numero % 10));
}

void LCD_Limpiar(void)
{
    LCD_Cmd(0x01);
}
