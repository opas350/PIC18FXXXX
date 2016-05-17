/* 
 * File:   PWM.c
 *
 * Created on November 11, 2015, 5:03 PM
 */

// https://www.mathsisfun.com/binary-decimal-hexadecimal-converter.html

//http://www.wolframalpha.com/input/?i=x%2F100+%3D+y%2F(4*(z%2B1)),+x+%3D25+,+z%3D24,+y

//http://www.wolframalpha.com/input/?i=x+%3D+%28y+%2B1%29*%284%29*%281%2F16000000%29*%28z%29%2C+x%3D%281%2F10000%29%2C+z+%3D16+%2C+y

// Freq = 10 KHz

#include <p18f45k50.h>
#include <xc.h>
#include <htc.h>

#define _XTAL_FREQ 16000000

void delay(int ms) {
	int x = ms / 10;
	while (x > 0) {
		__delay_ms(10);
		x--;
	}
}

void main(void) {
    ANSELC = 0;
    ANSELB = 0;
    
    TRISB = 0xFF;
    TRISCbits.TRISC2=1;
    
    CCPTMRS = 0;
    PR2 = 0x18;
    CCP1CON = 0x0C;
    CCPR1L = 0x00;
    T2CON = 0x06;
    TRISCbits.TRISC2=0;
    
    int CCP_cont, DC_cont = 0;


	while (1) {
        
        if (PORTBbits.RB7 == 0){
            CCP_cont++;
            DC_cont++;
            
			if (CCP_cont > 25) {
				CCP_cont = 25;
				DC_cont = 0;
			}   
            
			if (CCP_cont == 4 | CCP_cont == 9 | CCP_cont == 14 | CCP_cont == 19 | CCP_cont == 24) {
				CCP_cont++;
				DC_cont = 0;
			}
            while(PORTBbits.RB7==0);
            __delay_ms(10);
            __delay_ms(10);            
        }
        
        if (PORTBbits.RB6 == 0){
            CCP_cont--;
            DC_cont--;
			if (CCP_cont < 0) {
				CCP_cont = 0;
				DC_cont = 0;
			}
			if (CCP_cont == 4 | CCP_cont == 9 | CCP_cont == 14 | CCP_cont == 19 | CCP_cont == 24) {
				CCP_cont--;
				DC_cont = 3;
			}
            while(PORTBbits.RB6==0);
            __delay_ms(10);
            __delay_ms(10);            
        }
        
     CCPR1L = CCP_cont;
     CCP1CONbits.DC1B = DC_cont;
    }
}