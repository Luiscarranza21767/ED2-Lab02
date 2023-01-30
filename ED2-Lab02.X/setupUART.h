/* 
 * File:   
 * Author: Luis Carranza
 * Comments:
 * Revision history: 24/10/22
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef setup_UART
#define	setup_UART

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

// TODO Insert appropriate #include <>

// TODO Insert declarations

void UART_mode_config(uint8_t mode);

void UART_RX_config(uint16_t baudrate);

void UART_TX_config(uint16_t baudrate);

void UART_write_char(char character);

char UART_read_char(void);


#endif	/* XC_HEADER_TEMPLATE_H */