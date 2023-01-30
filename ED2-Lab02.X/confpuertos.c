/* 
 * File:   confpuertos.h
 * Author: Pablo
 *
 * Created on 19 de enero de 2023, 05:36 PM
 */
#include "confpuertos.h"

void configpuertos(void){
    // Configuración del puerto B (interrupciones)
    TRISB = 0b11000000;
    PORTB = 0b11000000;
    INTCONbits.GIE = 1;         // Habilitar interrupciones globales
    ANSELH = 0;
    
    //
    
    TRISD = 0;
    PORTD = 0;
    TRISC = 0b10000000;
    PORTC = 0;
//    TRISCbits.TRISC0 = 0;
//    TRISCbits.TRISC1 = 0;
//    PORTCbits.RC0 = 0;
//    PORTCbits.RC1 = 0;

    
}
