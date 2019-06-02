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

int h1, h2, m1, m2;

void writeBit(char _bit)
{
  RB7 = 0; //clockPin PIN 11 SHCP
  RB5 = _bit;  //DATA PIN 14
  RB7 = 1;
  RB7 = 0;
}

void writeNumber(int num){
    RB6 = 0; //ST_CP PIN 12
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
    RB6 = 1; //ST_CP PIN 12
}

void main(void) {
    TRISB=0b00000000;
    PORTB = 0;
    
    h1 = 0;
    h2 = 0;
    m1 = 0;
    m2 = 0;

    while(1){
        RB1 = 1;
        RB2 = 0;
        RB3 = 0;
        RB4 = 0;
        writeNumber(h1);
        RB1 = 0;
        RB2 = 1;
        RB3 = 0;
        RB4 = 0;
        writeNumber(h2);
        RB1 = 0;
        RB2 = 0;
        RB3 = 1;
        RB4 = 0;
        writeNumber(m1);
        RB1 = 0;
        RB2 = 0;
        RB3 = 0;
        RB4 = 1;
        writeNumber(m2);
        if (1 == 0){
            m2 = m2 + 1;
            if (m2 > 9){
                m2 = 0;
                m1 = m1 + 1;
            }
            if (m1 > 5){
                m1 = 0;
                h1 = h1 + 1;
            }
            if (h2 > 9){
                h2 = 0;
                h1 = h1 + 1;
            }
            if (h1 > 2){
                h1 = 0;
            }
        }
    }
    return;
}
