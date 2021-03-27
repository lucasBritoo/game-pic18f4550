#include	<xc.h>
#include <stdio.h>
#include <pic18f4550.h>
#include "config.h"
#include "lcd.h"


#define _XTAL_FREQ 20000000
#define led PORTBbits.RB0
#define botao PORTBbits.RB1
#define led2 PORTBbits.RB2
//char serial;
char envia = 'H';
int x =0;

void __interrupt(high_priority) tmr (void){
    if(RCIF){
        
        char serial = RCREG;
        lcd_putch(serial);
        //x = x+1;
        RCIF =0;
        
        TXREG = envia;
    }
}



void main(void) {
    configura();
    PORTD = 0;
    PORTE = 0;
    
    lcd_init();     //inicia o lcd
    lcd_clear();
    led = 0;
    led2 = 0;
    
    //lcd_puts("OIEE");
    //caractereEspecial();
    lcd_player();
    //lcd_desenhaPlayer();
    lcd_desenhaObstaculo();
    
    char posA1, posA2, posA3, posA4, posA5, posA6;
    
    posA1 = posA2 = posA3 = posA4 = posA5= posA6 = 0x8F;
    int pos2 = 0xCF+3;
    int x, flagA;
    char pos = 0xBF;
    x = flagA = 0;
     
    while(1){
       
        
        //lc_movimentoObstaculo(pos);
        /*pos += 1;
        led =1;
        __delay_ms(1000);
        //lcd_movimentoObstaculo(0);
        led = 0;*/
        __delay_ms(1000);
        
        posA1 = lcd_movimentoObstaculo(posA1);
       
        switch(x) {
            case 4:
                posA2 = lcd_movimentoObstaculo(posA2);
                flagA = 1;
                break;
            case 10:
                posA3 = lcd_movimentoObstaculo(posA3);
                flagA = 2;
                break;
            case 12:
                posA4 = lcd_movimentoObstaculo(posA4);
                flagA = 3;
                break;
            case 16:
                posA5 = lcd_movimentoObstaculo(posA5);
                flagA = 4;
                break;
            case 19:
                posA6 = lcd_movimentoObstaculo(posA6);
                flagA = 5;
                break;
            case 23:
                flagA = 6;
                posA1 = 0xBF;
                x = 0;
                break;
        }
        
        switch(flagA){
            case 1:
                posA2 = lcd_movimentoObstaculo(posA2);
                break;
            case 2:
                posA1 = lcd_movimentoObstaculo(posA1);
                posA2 = lcd_movimentoObstaculo(posA2);
                break;
            case 3:
                posA1 = lcd_movimentoObstaculo(posA1);
                posA2 = lcd_movimentoObstaculo(posA2);
                posA3 = lcd_movimentoObstaculo(posA3);
                break;
            case 4:
                posA1 = lcd_movimentoObstaculo(posA1);
                posA2 = lcd_movimentoObstaculo(posA2);
                posA3 = lcd_movimentoObstaculo(posA3);
                posA4 = lcd_movimentoObstaculo(posA4);
                break;
            case 5:
                posA1 = lcd_movimentoObstaculo(posA1);
                posA2 = lcd_movimentoObstaculo(posA2);
                posA3 = lcd_movimentoObstaculo(posA3);
                posA4 = lcd_movimentoObstaculo(posA4);
                posA5 = lcd_movimentoObstaculo(posA5);
                break;
            case 6:
                posA1 = lcd_movimentoObstaculo(posA1);
                posA2 = lcd_movimentoObstaculo(posA2);
                posA3 = lcd_movimentoObstaculo(posA3);
                posA4 = lcd_movimentoObstaculo(posA4);
                posA5 = lcd_movimentoObstaculo(posA5);
                posA6 = lcd_movimentoObstaculo(posA6);
                break;
        }
        
        
        x++;
        
    }
    
}


