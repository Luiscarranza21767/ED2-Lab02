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
    INTCONbits.RBIE = 1;    // Habilita interrupción del puerto B
    INTCONbits.RBIF = 0;    // Apaga la bandera de interrupción del puerto B
    IOCB = 0b11000000;      // Habilita la interrupción en cambio (IoC)
    WPUB = 0b11000000;      // Habilita el Weak Pull-Up en el puerto B
    OPTION_REGbits.nRBPU = 0;   // Deshabilita el bit de RBPU
    
    //
    
    TRISD = 0;
    PORTD = 0;
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    PORTCbits.RC0 = 0;
    PORTCbits.RC1 = 0;
    
}
