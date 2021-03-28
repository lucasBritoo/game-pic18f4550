#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
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

void movA(char *p, char *a, char *flag){
    *p = lcd_movimentoObstaculo(*p);
    if(*a >= 16){
        *p = 0x8F;
        *a = 0;
        *flag = 0;
    }
    else{
        //*p = lcd_movimentoObstaculo(*p);
        *a = *a + 1;
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
    lcd_player();
    lcd_desenhaObstaculo();
    
    char a1, a2, a3, a4, a5, a6;
    char p1, p2, p3, p4, p5, p6;
    char flag1, flag2, flag3, flag4, flag5, flag6;
    
    p1 = p2 = p3 = p4 = p5 = p6 = 0x8F;
    a1 = a2 = a3 = a4 = a5 = a6 = 0;
    flag1 = flag2 = flag3 = flag4 = flag5 = flag6 = 0;
 
    x =0;
     
    while(1){
       
       switch(a1){
           case 4:
               lcd_desenhaObstaculo();
               flag2 = 1;
               break;
           case 7:
               lcd_desenhaObstaculo();
               flag3 = 1;
               break;
           case 9:
               lcd_desenhaObstaculo();
               flag4 = 1;
               break;
           case 12:
               lcd_desenhaObstaculo();
               flag5 = 1;
               break;
           case 15:
               lcd_desenhaObstaculo();
               flag6 = 1;
               break;
       }
       
       if(flag2 == 1) movA(&p2, &a2, &flag2);
       
       if(flag3 == 1) movA(&p3, &a3, &flag3);
       
       if(flag4 == 1) movA(&p4, &a4, &flag4);
       
       if(flag5 == 1) movA(&p5, &a5, &flag5);
       
       if(flag6 == 1) movA(&p6, &a6, &flag6);
       
       movA(&p1, &a1, &flag1);
       
      __delay_ms(2000);
    }
    
}