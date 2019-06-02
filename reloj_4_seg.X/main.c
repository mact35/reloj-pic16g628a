/*
 * File:   main.c
 * Author: mact3
 *
 * Created on 29 de mayo de 2019, 11:34 PM
 */

#pragma config FOSC = INTOSCCLK // Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)         
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)         
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)         
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital input, MCLR internally tied to VDD)         
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)         
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)         
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)         
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)  
#define _XTAL_FREQ 4000000 // Internal oscillator  
#include <xc.h>

int x;

void writeBit(char _bit)
{
  RB7 = 0; //clockPin PIN 11 SHCP
  RB5 = _bit;  //DATA PIN 14
  RB7 = 1;
  RB7 = 0;
}

void writeNumber(int num){
    switch (num)
    {
        case 1:
            writeBit(1); //H
            writeBit(1); //G
            writeBit(1); //F
            writeBit(1); //E
            writeBit(1); //D
            writeBit(0); //C
            writeBit(0); //B
            writeBit(1); //A
            break;
        case 2:
            writeBit(1); //H
            writeBit(0); //G
            writeBit(1); //F
            writeBit(0); //E
            writeBit(0); //D
            writeBit(1); //C
            writeBit(0); //B
            writeBit(0); //A
            break;
        case 3:
            writeBit(1); //H
            writeBit(0); //G
            writeBit(1); //F
            writeBit(1); //E
            writeBit(0); //D
            writeBit(0); //C
            writeBit(0); //B
            writeBit(0); //A
            break;
        case 4:
            writeBit(1); //H
            writeBit(0); //G
            writeBit(0); //F
            writeBit(1); //E
            writeBit(1); //D
            writeBit(0); //C
            writeBit(0); //B
            writeBit(1); //A
            break;
        case 5:
            writeBit(1); //H
            writeBit(0); //G
            writeBit(0); //F
            writeBit(1); //E
            writeBit(0); //D
            writeBit(0); //C
            writeBit(1); //B
            writeBit(0); //A
            break;
        case 6:
            writeBit(1); //H
            writeBit(0); //G
            writeBit(0); //F
            writeBit(0); //E
            writeBit(0); //D
            writeBit(0); //C
            writeBit(1); //B
            writeBit(0); //A
            break;
        case 7:
            writeBit(1); //H
            writeBit(1); //G
            writeBit(1); //F
            writeBit(1); //E
            writeBit(1); //D
            writeBit(0); //C
            writeBit(0); //B
            writeBit(0); //A
            break;
        case 8:
            writeBit(1); //H
            writeBit(0); //G
            writeBit(0); //F
            writeBit(0); //E
            writeBit(0); //D
            writeBit(0); //C
            writeBit(0); //B
            writeBit(0); //A
            break;
        case 9:
            writeBit(1); //H
            writeBit(0); //G
            writeBit(0); //F
            writeBit(1); //E
            writeBit(0); //D
            writeBit(0); //C
            writeBit(0); //B
            writeBit(0); //A
            break;
        case 0:
            writeBit(1); //H
            writeBit(1); //G
            writeBit(0); //F
            writeBit(0); //E
            writeBit(0); //D
            writeBit(0); //C
            writeBit(0); //B
            writeBit(0); //A
            break;
            
    }
    
}

void write()
{
    for(x=0; x<10; x++)
    {
        RB6 = 0; //ST_CP PIN 12
        writeNumber(x);
        RB6 = 1;
        __delay_ms(500);
    }
}

void main(void) {
    TRISB=0b00000000;
    PORTB = 0;
    
    while(1){
        RB1 = 1;
        RB2 = 0;
        RB3 = 0;
        RB4 = 0;
        write();
        RB1 = 0;
        RB2 = 1;
        RB3 = 0;
        RB4 = 0;
        write();
        RB1 = 0;
        RB2 = 0;
        RB3 = 1;
        RB4 = 0;
        write();
        RB1 = 0;
        RB2 = 0;
        RB3 = 0;
        RB4 = 1;
        write();
    }
    return;
}