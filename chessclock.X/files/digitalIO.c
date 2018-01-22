/** 
 * @file  digitalIO.c
 * @author Tobias Haag, Felix S��, Jan Schneider, Marcus Schoch
 * 
 * @brief Bit deklaration der verschiedenen F�lle, beispielsweise LED an/aus oder Taster gedr�ckt/nicht gedr�ckt.
 * Au�erdem Erstellung von digitalRead und digitalWrite um die Bits auszulesen bzw zu schreiben.
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
void initPin(uint16_t pin) {
    switch(pin) {
        case LED_1:
            ANSELBbits.ANSB8=0;   //Digital I/O
            CNENBbits.CNIEB8=0;   // Disable Interrrupt
            TRISBbits.TRISB8=0; // Input/Output
            CNPUBbits.CNPUB8=0; CNPDBbits.CNPDB8=0; // No Pull up or down
            
            break;
            
        case LED_2:
            ANSELBbits.ANSB9=0;   //Digital I/O
            CNENBbits.CNIEB9=0;   // Disable Interrrupt
            TRISBbits.TRISB9=0; // Input/Output
            CNPUBbits.CNPUB9=0; CNPDBbits.CNPDB9=0; // No Pull up or down
            
            break;
            
        case LED_3:
            ANSELBbits.ANSB10=0;   //Digital I/O
            CNENBbits.CNIEB10=0;   // Disable Interrrupt
            TRISBbits.TRISB10=0; // Input/Output
            CNPUBbits.CNPUB10=0; CNPDBbits.CNPDB10=0; // No Pull up or down

            break;
            
        case LED_4:
            ANSELBbits.ANSB11=0;   //Digital I/O
            CNENBbits.CNIEB11=0;   // Disable Interrrupt
            TRISBbits.TRISB11=0; // Input/Output
            CNPUBbits.CNPUB11=0; CNPDBbits.CNPDB11=0; // No Pull up or down
                
            break;
        
        case BUTTON_T0:
            //ANSELGbits.ANSG12=0;   //Digital I/O
            CNENGbits.CNIEG12=0;   // Disable Interrrupt
            TRISGbits.TRISG12=1; // Input/Output
            CNPUGbits.CNPUG12=0; CNPDGbits.CNPDG12=0; // No Pull up or down
            TRISGbits.TRISG12= 1; //Input
            CNPUGbits.CNPUG12=1;

            break;
        case BUTTON_T1:
            //ANSELGbits.ANSG13=0;   //Digital I/O
            CNENGbits.CNIEG13=0;   // Disable Interrrupt
            TRISGbits.TRISG13=1; // Input/Output
            CNPUGbits.CNPUG13=0; CNPDGbits.CNPDG13=0; // No Pull up or down
            TRISGbits.TRISG13= 1; //Input
            CNPUGbits.CNPUG13=1;

            break;
        
        case BUTTON_T2:
            //ANSELGbits.ANSG14=0;   //Digital I/O
            CNENGbits.CNIEG14=0;   // Disable Interrrupt
            TRISGbits.TRISG14=1; // Input/Output
            CNPUGbits.CNPUG14=0; CNPDGbits.CNPDG14=0; // No Pull up or down
            TRISGbits.TRISG14= 1; //Input
            CNPUGbits.CNPUG14=1;

            break;
            
        case BUTTON_T3:
            //ANSELGbits.ANSG15=0;   //Digital I/O
            CNENGbits.CNIEG15=0;   // Disable Interrrupt
            TRISGbits.TRISG15=1; // Input/Output
            CNPUGbits.CNPUG15=0; CNPDGbits.CNPDG15=0; // No Pull up or down
            TRISGbits.TRISG15= 1; //Input
            CNPUGbits.CNPUG15=1;
                
            break;
    }
}

/** 
 * @brief digital Read
 * @param pin
 * @pre !!!
 * @attention !!!
 */
uint8_t digitalRead(uint16_t pin) {
    switch(pin) {
        case BUTTON_T0:
            return PORTGbits.RG12;
            break;
        case BUTTON_T1:
            return PORTGbits.RG13;
            break;
        case BUTTON_T2:
            return PORTGbits.RG14;
            break;
        case BUTTON_T3:
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
        case LED_1:
            LATBbits.LATB8 = mode;
            break;
        case LED_2:
            LATBbits.LATB9 = mode;
            break;
        case LED_3:
            LATBbits.LATB10 = mode;
            break;
        case LED_4:
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
 * @brief readEncoder
 * @param -
 * @pre !!!
 * @attention !!!
 */
int8_t readEncoder() {
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