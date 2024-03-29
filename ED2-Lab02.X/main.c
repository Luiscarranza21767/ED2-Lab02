/* Universidad del Valle de Guatemala
 IE3054 Electrónica Digital 2
 Autor: Luis Pablo Carranza
 Compilador: XC8, MPLAB X IDE (v6.00)
 Proyecto: Laboratorio No.02
 Hardware PIC16F887
 Creado: 26/01/23
 Última Modificación: 30/01/23*/

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT // Oscillator Selection bits (INTOSC 
//oscillator without clock out)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and 
//can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR 
//pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code 
//protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code 
//protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/
//External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-
//Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin 
//has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit 
//(Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits 
//(Write protection off)

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

#include "LCD.h"
#include "oscilador.h"
#include "setupADC.h"
#include "confpuertos.h"
#include "conversiones.h"
#include "setupUART.h"

#define _XTAL_FREQ 1000000
float lecADC0;
int lecADC1;
uint16_t valADC0;
uint16_t valADC1;
uint8_t cont;
char indicador;
char unidades;
char decimas;
char centesimas;

void __interrupt() isr (void){
    
    if(PIR1bits.ADIF){
        if(ADCON0bits.CHS == 0){
            lecADC0 = ADRESH;
        }
        else if(ADCON0bits.CHS == 1){
            lecADC1 = ADRESH;
        }
        ADIF = 0;                   // Apaga la bandera del ADC
    }
    
    if(PIR1bits.RCIF){
        indicador = UART_read_char(); //Realiza la lectura de UART
        if (indicador == '+'){
            cont = cont + 1;
        }
        else if(indicador == '-'){
            cont = cont - 1;
        }
        
        PIR1bits.RCIF = 0;  // Limpia la bandera
    }
}

void main(void) {
    setupINTOSC(4);     //Oscilador a 1MHz
    configpuertos();
    ADC_config(0x03);   //0x03 = 0b00000011 -> AN0 y AN1 son analógicos
    UART_mode_config(3);    //Configurar UART como 16 bit asíncrono
    UART_RX_config(9600);
    Lcd_Init();
    Lcd_Clear();
    Lcd_Set_Cursor(1,2);
    Lcd_Write_String("S1:   S2:   S3:"); 
    cont = 0;
    
    while(1){
        
        // Mostrar el valor del primer pot
        ADC_read(0);
        valADC0 = mapeo(lecADC0, 0, 255, 0, 500);
        unidades = inttochar(descomponer(2, valADC0));
        Lcd_Set_Cursor(2,1);
        Lcd_Write_Char(unidades);
        Lcd_Set_Cursor(2,2);
        Lcd_Write_Char('.');
        decimas = inttochar(descomponer(1, valADC0));
        Lcd_Set_Cursor(2,3);
        Lcd_Write_Char(decimas);
        centesimas = inttochar(descomponer(0, valADC0));
        Lcd_Set_Cursor(2,4);
        Lcd_Write_Char(centesimas);
        Lcd_Set_Cursor(2,5);
        Lcd_Write_Char('V');
        
        //Mostrar el valor del segundo pot
        ADC_read(1);
        valADC1 = mapeo(lecADC1, 0, 255, 0, 500);
        unidades = inttochar(descomponer(2, valADC1));
        Lcd_Set_Cursor(2,7);
        Lcd_Write_Char(unidades);
        Lcd_Set_Cursor(2,8);
        Lcd_Write_Char('.');
        decimas = inttochar(descomponer(1, valADC1));
        Lcd_Set_Cursor(2,9);
        Lcd_Write_Char(decimas);
        centesimas = inttochar(descomponer(0, valADC1));
        Lcd_Set_Cursor(2,10);
        Lcd_Write_Char(centesimas);
        Lcd_Set_Cursor(2,11);
        Lcd_Write_Char('V');
        
        unidades = inttochar(descomponer(2, cont));
        Lcd_Set_Cursor(2,13);
        Lcd_Write_Char(unidades);
        decimas = inttochar(descomponer(1, cont));
        Lcd_Set_Cursor(2,14);
        Lcd_Write_Char(decimas);
        centesimas = inttochar(descomponer(0, cont));
        Lcd_Set_Cursor(2,15);
        Lcd_Write_Char(centesimas);
    }
}
