/*
 * File:   oscilador.c
 * Author: Luis Pablo Carranza
 *
 * Created on 24 de octubre de 2022, 11:37 PM
 */
#include <xc.h> // include processor files - each processor file is guarded. 
#include "setupUART.h"

void UART_mode_config(uint8_t mode){
    // Configuración del modo de operación de EUSART
    if(mode == 0){              // 8 bits asíncrono
        BAUDCTLbits.BRG16 = 0;
        TXSTAbits.BRGH = 0; 
        TXSTAbits.SYNC = 0;     
    }
    else if(mode == 1){         // 8 bits asíncrono
        BAUDCTLbits.BRG16 = 0;
        TXSTAbits.BRGH = 1;  
        TXSTAbits.SYNC = 0;     
    }
    else if(mode == 2){         // 16 bits asíncrono
        BAUDCTLbits.BRG16 = 1;
        TXSTAbits.BRGH = 0;  
        TXSTAbits.SYNC = 0;    
    }
    else if(mode == 3){         // 16 bits asíncrono
        BAUDCTLbits.BRG16 = 1;
        TXSTAbits.BRGH = 1;  
        TXSTAbits.SYNC = 0;     // Modo asíncrono
    }
    else if(mode == 4){         // 8 bits síncrono
        BAUDCTLbits.BRG16 = 0;
        TXSTAbits.BRGH = 1;  
        TXSTAbits.SYNC = 1;     
    }
    else if(mode == 5){         // 16 bits síncrono
        BAUDCTLbits.BRG16 = 1;
        TXSTAbits.BRGH = 0;  
        TXSTAbits.SYNC = 1;   
    }
    
    RCSTAbits.SPEN = 1;     // Habilitar módulo UART
    
    
}
void UART_RX_config(uint16_t baudrate){
    if (baudrate == 9600){
        SPBRG = 25;             // Valor calculado para 9600 baudios-16 bit asíncrono
        SPBRGH = 0;
    }
    RCSTAbits.CREN = 1;     // Habilitar la recepción
    PIE1bits.RCIE = 1;      // Habilitar interrupción por recepción
    PIR1bits.RCIF = 0;      // Limpia la bandera de recepción
    INTCONbits.PEIE = 1;    // Habilita interrupción de periféricos
    INTCONbits.GIE = 1;     // Habilita interrupciones globales si no estaba activada
}

void UART_TX_config(uint16_t baudrate){
    if (baudrate == 9600){
        SPBRG = 25;             // Valor calculado para 9600 baudios-16 bit asíncrono
        SPBRGH = 0;
    }
    TXSTAbits.TXEN = 1;     // Habilitar la transmisión
    PIR1bits.TXIF = 0;      // Limpiar la bandera
}

void UART_write_char(char character){
    TXREG = character;
}

char UART_read_char(void){
    return RCREG;
}