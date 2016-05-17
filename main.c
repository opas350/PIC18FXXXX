/* 
 * Author: Ing. Sebastián Estrada García
 *
 * Created on November 18, 2015, 1:36 AM
 */

#include <xc.h>
#include <p18f45k50.h>
#include <htc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _XTAL_FREQ 16000000     //Definimos nuestro cristal de 16 MHz


//Función Delay en ms
void delay(int ms) {
	int x = ms / 10;
	while (x > 0) {
		__delay_ms(10);
		x--;
	}
}

delay1seg(){
    for(int i=0;i<100;i++){
        __delay_ms(10);
    }
}

//Función para transmitir un dato de tipo char, este prototipo es necesario
//para que la función printf funcione.
void putch(char data)
{
    while(!PIR1bits.TXIF && !TXSTA1bits.TRMT);
    TXREG1 = data;
}

void main() {
    ANSELC = 0;         //Registro C como digital
    ANSELB = 0;         //Registro B como digital

    //Configuración del EUSART
    TXSTA1 = 0x20; 
    RCSTA1 = 0x90;
    BAUDCON1 = 0x00;
    SPBRG1 = 25; // Baud Rate es 9600
    
    TRISCbits.RC6 = 0; // Tx es una salida digital
    LATCbits.LC6 = 0;  // Limpio la salida
    TRISCbits.RC7 = 1; // Rx es una entrada digital
    
    PIR1bits.RCIF = 0; // El buffer de recepción está vacío
    PIR1bits.TXIF = 1; // El buffer de transmisión está vacío 
   
        printf("A\n\r"); //Unsigned interger value 
        delay1seg();
      
  

}