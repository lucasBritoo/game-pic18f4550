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
        *a = 0;
        *flag = 0;
        *p = 0x8F;
        
    }
    else{
        *a = *a + 1;
    }
}

void movB(char *q, char *b , char *flag){
    *q = lcd_movimentoObstaculo(*q);
    
    if(*b >= 16){
        lcd_apaga();
        *b = 0;
        *flag = 0;
        *q = 0xCF;
    }
    else *b = *b + 1;
    

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
    lcd_desenhaObstaculoA();
    
    char a1, a2, a3, a4, b1, b2, b3, b4, b5;
    char p1, p2, p3, p4, q1, q2, q3, q4, q5;
    
    char flagA1, flagA2, flagA3, flagA4, flagB1, flagB2, flagB3, flagB4, flagB5;
    
    p1 = p2 = p3 = p4 = 0x8F;
    q1 = q2 = q3 = q4 = q5 = 0xCF;
    
    a1 = a2 = a3 = a4 = b1 = b2 = b3 = b4 = b5 = 0;
    
    flagA1 = flagA2 = flagA3 = flagA4 = flagB1 = flagB2 = flagB3 = flagB4 = flagB5 = 0;
 
    x =0;
     
    while(1){
       
       switch(a1){
           case 2:
               lcd_desenhaObstaculoB();
               flagB1 = 1;
               break;
           case 4:
               lcd_desenhaObstaculoA();
               flagA2 = 1;
               break;
           case 6:
               lcd_desenhaObstaculoB();
               flagB2 = 1;
               break;
           case 8:
               lcd_desenhaObstaculoA();
               flagA3 = 1;
               break;  
           case 10: 
               lcd_desenhaObstaculoB();
               flagB3 = 1;
               break;
            case 11: 
               lcd_desenhaObstaculoB();
               flagB4 = 1;
               break;
            case 13:
               lcd_desenhaObstaculoA();
               flagA4 = 1;
               break;
           case 15:
               lcd_desenhaObstaculoB();
               flagB5 = 1;
               break;
       }
       
       if(flagA2 == 1) movA(&p2, &a2, &flagA2);
       
       if(flagA3 == 1) movA(&p3, &a3, &flagA3);
       
       if(flagA4 == 1) movA(&p4, &a4, &flagA4);
       
       if(flagB1 == 1) movB(&q1, &b1, &flagB1);
       
       if(flagB2 == 1) movB(&q2, &b2, &flagB2);
       
       if(flagB3 == 1) movB(&q3, &b3, &flagB3);
       
       if(flagB4 == 1) movB(&q4, &b4, &flagB4);
       
       if(flagB5 == 1) movB(&q5, &b5, &flagB5);
       
      movA(&p1, &a1, &flagA1);
       
      __delay_ms(1000);
    }
    
}