/*
 *	LCD interface example
 *	Uses routines from delay.c
 *	This code will interface to a standard LCD controller
 *	like the Hitachi HD44780. It uses it in 4 bit mode, with
 *	the hardware connected as follows (the standard 14 pin 
 *	LCD connector is used):
 *	
 *	PORTD bits 0-3 are connected to the LCD data bits 4-7 (high nibble)
 *	PORTA bit 3 is connected to the LCD RS input (register select)
 *	PORTA bit 1 is connected to the LCD EN bit (enable)
 *	
 *	To use these routines, set up the port I/O (TRISA, TRISD) then
 *	call lcd_init(), then other routines as required.
 *	
 */

#ifndef _XTAL_FREQ
 // Unless specified elsewhere, 4MHz system frequency is assumed
 #define _XTAL_FREQ 20000000
#endif


#include	<xc.h>
#include	"lcd.h"

#define	LCD_RS LE0
#define LCD_EN LE1
//#define	LCD_RW LE2

#define LCD_DATA	PORTD

#define	LCD_STROBE()	((LCD_EN = 1),(LCD_EN=0))

/* write a byte to the LCD in 4 bit mode */

void
lcd_write(unsigned char c)
{
	__delay_ms(1);
    LCD_DATA = ( c );
	LCD_STROBE();
//	LCD_DATA = ( c );
//	LCD_STROBE();
}

/*
 * 	Clear and home the LCD
 */

void
lcd_clear(void)
{
	LCD_RS = 0;
	lcd_write(0x01);
	__delay_ms(2);
}

/* write a string of chars to the LCD */

void
lcd_puts(const char * s)
{
	LCD_RS = 1;	// write characters
	while(*s)
		lcd_write(*s++);
}

/* write one character to the LCD */

void
lcd_putch(char c)
{
	LCD_RS = 1;	// write characters
	lcd_write( c );
}


/*
 * Go to the specified position
 */

void
lcd_goto(unsigned char pos)
{
	LCD_RS = 0;
	lcd_write(0x80+pos);
}


void lcd_player(){
    
    LCD_RS = 0;
    lcd_write(0x40);
    
    LCD_RS = 1;
    lcd_write(0x0E);
    lcd_write(0x0A);
    lcd_write(0x1F);
    lcd_write(0x1F);
    lcd_write(0x1F);
    lcd_write(0x0A);
    lcd_write(0x0A);
    lcd_write(0x00);
    
    __delay_ms(50);
    
    LCD_RS = 0;
    lcd_write(0x48);
    
    LCD_RS = 1;
    lcd_write(0x0A);
    lcd_write(0x1F);
    lcd_write(0x15);
    lcd_write(0x1F);
    lcd_write(0x11);
    lcd_write(0x1F);
    lcd_write(0x0A);
    lcd_write(0x00);
    
    __delay_ms(50);
}


void lcd_desenhaPlayer(){
    LCD_RS = 0;
    lcd_write(0xC9);
    
    LCD_RS = 1;
    lcd_write(0x00);
   
}

void lcd_desenhaObstaculoA(){
    LCD_RS = 0;
    lcd_write(0x8F);
    
    LCD_RS = 1;
    lcd_write(0x09);
}

void lcd_desenhaObstaculoB(){
    LCD_RS = 0;
    lcd_write(0xCF);
    
    LCD_RS = 1;
    lcd_write(0x09);
}


void lcd_deslocaEsquerda(){
    
    LCD_RS = 0;
    lcd_write(0x8C);
    
    LCD_RS = 0;
    lcd_write(0x18);
}

char lcd_movimentoObstaculo(char pos){
    
    LCD_RS = 0;
    lcd_write(pos+1);
    lcd_puts(" ");
 
    LCD_RS = 0;
    lcd_write(pos--);
    
    LCD_RS = 1;
    lcd_write(0x09);
    
    return pos;
}

void lcd_apaga(){
    LCD_RS = 0;
    lcd_write(0xC0);
    lcd_puts(" ");

}

void lcd_movimentoPlayer(char movimento){
    
    
 
    if(movimento == 1){
       LCD_RS = 0;
       lcd_write(0xC0);
       lcd_putch(' ');
       
       LCD_RS = 0;
       lcd_write(0x80);
       
       LCD_RS = 1;
       lcd_write(0x00);
    }
    else{
        LCD_RS = 0;
        lcd_write(0x80);
        lcd_putch(' ');
        
        LCD_RS = 0;
        lcd_write(0xC0);
        
        LCD_RS = 1;
        lcd_write(0x00);
    }
    
}

/* initialise the LCD - put into 4 bit mode */
void
lcd_init()
{
	char init_value;

	
	init_value = 0x03;
	LCD_RS = 0;
	LCD_EN = 0;
//	LCD_RW = 0;
	
	__delay_ms(15);	// wait 15mSec after power applied,
	LCD_DATA	 = init_value;
	LCD_STROBE();
	__delay_ms(5);
	LCD_STROBE();
	__delay_us(200);
	LCD_STROBE();
	__delay_us(200);
	LCD_DATA = 2;	// Four bit mode
	LCD_STROBE();

	lcd_write(0x38); // Set interface length
	lcd_write(0x06); // Set entry Mode
	lcd_write(0x0C); // Display On, Cursor On, Cursor Blink
	lcd_clear();	// Clear screen
	
}