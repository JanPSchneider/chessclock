/** 
 * @file  digitalIO.c
 * @author Tobias Haag, Felix Süß, Jan Schneider, Marcus Schoch
 * 
 * @brief Bit deklaration der verschiedenen Fälle, beispielsweise LED an/aus oder Taster gedrückt/nicht gedrückt.
 * Außerdem Erstellung von digitalRead und digitalWrite um die Bits auszulesen bzw zu schreiben.
 * 
 * @date Created on 16.01.2017
 */

#include <stdint.h>
#include <stdbool.h>
#include <p33EP512MU810.h>

#include "digitalIO.h"

// SW 0..3: PG12..15
// LED 0...3: PB8..11
// INC.A=G0; INC.B=G1; INC.SW=G9

/** 
 * @brief pinMode
 * @param pin, mode
 * @pre !!!
 * @attention !!!
 */
void pinMode(uint16_t pin, uint8_t mode) {
    switch(pin) {
        case LED200:
            ANSELBbits.ANSB8=0;   //Digital I/O
            CNENBbits.CNIEB8=0;   // Disable Interrrupt
            if(mode == INPUT || mode == OUTPUT) {
                TRISBbits.TRISB8=mode; // Input/Output
                CNPUBbits.CNPUB8=0; CNPDBbits.CNPDB8=0; // No Pull up or down
            } else if (mode == INPUT_PULLUP){
                TRISBbits.TRISB8= 1; //Input
                CNPUBbits.CNPUB8=1;
            } else if(mode == INPUT_PULLDOWN) {
                TRISBbits.TRISB8= 1; // Input
                CNPDBbits.CNPDB8=1;
            }
            break;
            
        case LED201:
            ANSELBbits.ANSB9=0;   //Digital I/O
            CNENBbits.CNIEB9=0;   // Disable Interrrupt
            if(mode == INPUT || mode == OUTPUT) {
                TRISBbits.TRISB9=mode; // Input/Output
                CNPUBbits.CNPUB9=0; CNPDBbits.CNPDB9=0; // No Pull up or down
            } else if (mode == INPUT_PULLUP){
                TRISBbits.TRISB9= 1; //Input
                CNPUBbits.CNPUB9=1;
            } else if(mode == INPUT_PULLDOWN) {
                TRISBbits.TRISB9= 1; // Input
                CNPDBbits.CNPDB9=1;
            }
            break;
            
        case LED202:
            ANSELBbits.ANSB10=0;   //Digital I/O
            CNENBbits.CNIEB10=0;   // Disable Interrrupt
            if(mode == INPUT || mode == OUTPUT) {
                TRISBbits.TRISB10=mode; // Input/Output
                CNPUBbits.CNPUB10=0; CNPDBbits.CNPDB10=0; // No Pull up or down
            } else if (mode == INPUT_PULLUP){
                TRISBbits.TRISB10= 1; //Input
                CNPUBbits.CNPUB10=1;
            } else if(mode == INPUT_PULLDOWN) {
                TRISBbits.TRISB10= 1; // Input
                CNPDBbits.CNPDB10=1;
            }
            break;
            
        case LED203:
            ANSELBbits.ANSB11=0;   //Digital I/O
            CNENBbits.CNIEB11=0;   // Disable Interrrupt
            if(mode == INPUT || mode == OUTPUT) {
                TRISBbits.TRISB11=mode; // Input/Output
                CNPUBbits.CNPUB11=0; CNPDBbits.CNPDB11=0; // No Pull up or down
            } else if (mode == INPUT_PULLUP){
                TRISBbits.TRISB11= 1; //Input
                CNPUBbits.CNPUB11=1;
            } else if(mode == INPUT_PULLDOWN) {
                TRISBbits.TRISB11= 1; // Input
                CNPDBbits.CNPDB11=1;
            }
            break;
        
        case SW200:
            //ANSELGbits.ANSG12=0;   //Digital I/O
            CNENGbits.CNIEG12=0;   // Disable Interrrupt
            if(mode == INPUT || mode == OUTPUT) {
                TRISGbits.TRISG12=mode; // Input/Output
                CNPUGbits.CNPUG12=0; CNPDGbits.CNPDG12=0; // No Pull up or down
            } else if (mode == INPUT_PULLUP){
                TRISGbits.TRISG12= 1; //Input
                CNPUGbits.CNPUG12=1;
            } else if(mode == INPUT_PULLDOWN) {
                TRISGbits.TRISG12= 1; // Input
                CNPDGbits.CNPDG12=1;
            }
            break;
        case SW201:
            //ANSELGbits.ANSG13=0;   //Digital I/O
            CNENGbits.CNIEG13=0;   // Disable Interrrupt
            if(mode == INPUT || mode == OUTPUT) {
                TRISGbits.TRISG13=mode; // Input/Output
                CNPUGbits.CNPUG13=0; CNPDGbits.CNPDG13=0; // No Pull up or down
            } else if (mode == INPUT_PULLUP){
                TRISGbits.TRISG13= 1; //Input
                CNPUGbits.CNPUG13=1;
            } else if(mode == INPUT_PULLDOWN) {
                TRISGbits.TRISG13= 1; // Input
                CNPDGbits.CNPDG13=1;
            }
            break;
        
        case SW202:
            //ANSELGbits.ANSG14=0;   //Digital I/O
            CNENGbits.CNIEG14=0;   // Disable Interrrupt
            if(mode == INPUT || mode == OUTPUT) {
                TRISGbits.TRISG14=mode; // Input/Output
                CNPUGbits.CNPUG14=0; CNPDGbits.CNPDG14=0; // No Pull up or down
            } else if (mode == INPUT_PULLUP){
                TRISGbits.TRISG14= 1; //Input
                CNPUGbits.CNPUG14=1;
            } else if(mode == INPUT_PULLDOWN) {
                TRISGbits.TRISG14= 1; // Input
                CNPDGbits.CNPDG14=1;
            }
            break;
            
        case SW203:
            //ANSELGbits.ANSG15=0;   //Digital I/O
            CNENGbits.CNIEG15=0;   // Disable Interrrupt
            if(mode == INPUT || mode == OUTPUT) {
                TRISGbits.TRISG15=mode; // Input/Output
                CNPUGbits.CNPUG15=0; CNPDGbits.CNPDG15=0; // No Pull up or down
            } else if (mode == INPUT_PULLUP){
                TRISGbits.TRISG15= 1; //Input
                CNPUGbits.CNPUG15=1;
            } else if(mode == INPUT_PULLDOWN) {
                TRISGbits.TRISG15= 1; // Input
                CNPDGbits.CNPDG15=1;
            }
            break;
    }
}

/** 
 * @brief digital Ream
 * @param pin
 * @pre !!!
 * @attention !!!
 */
uint8_t digitalRead(uint16_t pin) {
    switch(pin) {
        case SW200:
            return PORTGbits.RG12;
            break;
        case SW201:
            return PORTGbits.RG13;
            break;
        case SW202:
            return PORTGbits.RG14;
            break;
        case SW203:
            return PORTGbits.RG15;
            break;
            
        case INC_A:
            return PORTGbits.RG0;
            break;
        case INC_B:
            return PORTGbits.RG1;
            break;
        case INC_SW:
            return PORTGbits.RG9;
            break;
    }
    return 0;
}

/** 
 * @brief digitalWrite
 * @param pin, mode
 * @pre !!!
 * @attention !!!
 */
void digitalWrite(uint16_t pin, uint8_t mode) {
    switch(pin) {
        case LED200:
            LATBbits.LATB8 = mode;
            break;
        case LED201:
            LATBbits.LATB9 = mode;
            break;
        case LED202:
            LATBbits.LATB10 = mode;
            break;
        case LED203:
            LATBbits.LATB11= mode;
            break;
    }
}

/** 
 * @brief digitalWriteLEDs
 * @param mask
 * @pre !!!
 * @attention !!!
 */
void digitalWriteLEDs(uint16_t mask) {
    LATB &= 0xF0FF; // clear all four LEDs
    LATB |= (mask << 8); // set bits again
}

/** 
 * @brief initEncoder
 * @param -
 * @pre initialise the encode
 * @attention !!!
 */
void initEncoder() {
    // Set Encoder Pins as digital Inputs
    // Note: ANSEL G0,1 not existing, always digital
    ANSELGbits.ANSG9 = 0;
    TRISGbits.TRISG0 = 1;
    TRISGbits.TRISG1 = 1;
    TRISGbits.TRISG9 = 1;
    
    // Enable Pullup
    CNPUGbits.CNPUG0=1;
    CNPUGbits.CNPUG1=1;
    CNPUGbits.CNPUG9=1;
    
}

/** 
 * @brief readEncoderPulse
 * @param -
 * @pre !!!
 * @attention !!!
 */
int8_t readEncoderPulse() {
    bool inc_a = digitalRead(INC_A);
    while (inc_a == digitalRead(INC_A)) { // do nothing while state stays the same
        if (!digitalRead(INC_SW)) {
            return 0; // exit without change on switch press
        }
    }
    if (!inc_a == digitalRead(INC_B)) { // A == B means backwards rotating, else forwards
        return -1;
    } else {
        return 1;
    }
}

/** 
 * @brief initPiezo
 * @param -
 * @pre initialize the piezo
 * @attention !!!
 */
void initPiezo() {
    //Piezo Output
    ANSELGbits.ANSG8 = 0;
    TRISGbits.TRISG8 = 0;
    CNENGbits.CNIEG8 = 0;
}