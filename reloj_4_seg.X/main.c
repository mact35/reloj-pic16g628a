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
#define _XTAL_FREQ 4000000      // Internal oscillator  
#include <xc.h>

unsigned char h1 = 0, h2 = 0, m1 =2, m2 = 5, blink = 0, ant = 0;
unsigned short cnt = 0;
short tiempo = 915;
unsigned short acum = 5273;
unsigned short suma = 0;

    
void writeBit(char _bit)
{
  RB7 = 0; //clockPin PIN 11 SHCP
  RB5 = _bit;  //DATA PIN 14
  RB7 = 1;
  RB7 = 0;
}

void addMinute(){
    if (TMR0 == 255){
        cnt = cnt + 1;        
        if (ant != (cnt/10)){
            ant = cnt/10;
            blink = !blink; 
        }
        if (cnt >= tiempo){ 
            suma = suma + acum; 
            
            if (tiempo > 916){
                tiempo = 915;
                suma = 0;
                //acum = 5273;
            }
            if (suma >= 10000){
                suma = suma - 10000;
                tiempo = tiempo + 1;
                //acum = acum - 656;
                RB0 = !RB0;
            }
                   
            cnt = 0;            
            m2 = m2 + 1;
            if (m2 > 9){
                m2 = 0;
                m1 = m1 + 1;
            }
            if (m1 > 5){
                m1 = 0;
                h2 = h2 + 1;
            }
            if (h2 > 9){
                h2 = 0;
                h1 = h1 + 1;
            }
            if (h1 >= 2){
                if(h2 < 9 && h2 > 3 && h1 == 2){
                    h2 = 0;
                    h1 = 0;
                }
            }
        }
        //TMR0 = 0;
    }
}

void writeNumber(unsigned char num, unsigned char point){
    RB6 = 0; //ST_CP PIN 12
    switch (num)
    {
        case 1:
            writeBit(point); //H
            writeBit(1); //G
            writeBit(1); //F
            writeBit(1); //E
            writeBit(1); //D
            writeBit(0); //C
            writeBit(0); //B
            writeBit(1); //A
            break;
        case 2:
            writeBit(point); //H
            writeBit(0); //G
            writeBit(1); //F
            writeBit(0); //E
            writeBit(0); //D
            writeBit(1); //C
            writeBit(0); //B
            writeBit(0); //A
            break;
        case 3:
            writeBit(point); //H
            writeBit(0); //G
            writeBit(1); //F
            writeBit(1); //E
            writeBit(0); //D
            writeBit(0); //C
            writeBit(0); //B
            writeBit(0); //A
            break;
        case 4:
            writeBit(point); //H
            writeBit(0); //G
            writeBit(0); //F
            writeBit(1); //E
            writeBit(1); //D
            writeBit(0); //C
            writeBit(0); //B
            writeBit(1); //A
            break;
        case 5:
            writeBit(point); //H
            writeBit(0); //G
            writeBit(0); //F
            writeBit(1); //E
            writeBit(0); //D
            writeBit(0); //C
            writeBit(1); //B
            writeBit(0); //A
            break;
        case 6:
            writeBit(point); //H
            writeBit(0); //G
            writeBit(0); //F
            writeBit(0); //E
            writeBit(0); //D
            writeBit(0); //C
            writeBit(1); //B
            writeBit(0); //A
            break;
        case 7:
            writeBit(point); //H
            writeBit(1); //G
            writeBit(1); //F
            writeBit(1); //E
            writeBit(1); //D
            writeBit(0); //C
            writeBit(0); //B
            writeBit(0); //A
            break;
        case 8:
            writeBit(point); //H
            writeBit(0); //G
            writeBit(0); //F
            writeBit(0); //E
            writeBit(0); //D
            writeBit(0); //C
            writeBit(0); //B
            writeBit(0); //A
            break;
        case 9:
            writeBit(point); //H
            writeBit(0); //G
            writeBit(0); //F
            writeBit(1); //E
            writeBit(0); //D
            writeBit(0); //C
            writeBit(0); //B
            writeBit(0); //A
            break;
        case 0:
            writeBit(point); //H
            writeBit(1); //G
            writeBit(0); //F
            writeBit(0); //E
            writeBit(0); //D
            writeBit(0); //C
            writeBit(0); //B
            writeBit(0); //A
            break;
        case 10:
            writeBit(1); //H
            writeBit(1); //G
            writeBit(1); //F
            writeBit(1); //E
            writeBit(1); //D
            writeBit(1); //C
            writeBit(1); //B
            writeBit(1); //A
            break;
            
    }
    RB6 = 1; //ST_CP PIN 12
    addMinute();
}

void main(void) {
    TRISB = 0b00000000;
    PORTB = 0;
    OPTION_REG = 0b00000111;
    //TMR0 = 0;
    while(1){
        RB1 = 1;
        RB2 = 0;
        RB3 = 0;
        RB4 = 0;
        writeNumber(h1,1);
        writeNumber(10,1);
        RB1 = 0;
        RB2 = 1;
        RB3 = 0;
        RB4 = 0;
        writeNumber(h2,blink);
        writeNumber(10,1);         
        RB1 = 0;
        RB2 = 0;
        RB3 = 1;
        RB4 = 0;
        writeNumber(m1,blink);
        writeNumber(10,1);
        RB1 = 0;
        RB2 = 0;
        RB3 = 0;
        RB4 = 1;
        writeNumber(m2,1); 
        writeNumber(10,1);     
    }
    return;
}
