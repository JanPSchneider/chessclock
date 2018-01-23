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
#include "lcd.h"

#include "digitalIO.h"

// SW 0..3: PG12..15
// LED 0...3: PB8..11
// INC.A=G0; INC.B=G1; INC.SW=G9

/** 
 * @brief Initialisiert die Pins. Setzt die Bits der einzelnen Pins
 * @param pin
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
        default:
            LCD_ClearScreen();
            LCD_PutString("! initPin", 16);
            break;
    }
}

/** 
 * @brief ließt die einzelnen bits der Buttons T0-T3 aus, sowie die Bits des Inkrementers.
 * @param pin
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
            
        default:
            LCD_ClearScreen();
            LCD_PutString("! digitalRead", 16);
            break;
    }
    return 0;
}

/** 
 * @brief Steuert die LEDs an.
 * @param pin, mode
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
        default:
            LCD_ClearScreen();
            LCD_PutString("! digitalWrite", 16);
            break;
    }
}

/** 
 * @brief Setzt die Bits der LEDs, Schaltet die LEDs somit an oder aus
 * @param overwrite
 */
void digitalWriteLEDs(uint16_t overwrite) {
    LATB &= 0xF0FF; // schalte alle LEDs aus
    LATB |= overwrite; // setzt bits neu
}

/** 
 * @brief Initialisiert den Encoder. Setzt die Pins des Encoders als digitale Inputs
 * @attention ANSEL G0,1 existiert nicht, alles digitale Eingänge
 */
void initEncoder() {
   
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
 * @brief Ließt die Werte des Drehencoders aus.
 */
int8_t readEncoder() {
    bool inc_a = digitalRead(INC_A);
    while (inc_a == digitalRead(INC_A)) { // Solange nicht gedreht wird, tue nichts!
        if (!digitalRead(INC_SW)) {
            return 0; // bei Tastendruck verlassen ohne Änderungen.
        }
    }
    if (!inc_a == digitalRead(INC_B)) { // A == B bedeutet rückwärts, andernfalls vorwärts
        return -1;
    } 
    else {
        return 1;
    }
}

/** 
 * @brief Initialisiert den Piezo. Legt die Bits des Piezo fest.
 */
void initPiezo() {
    //Piezo Output
    ANSELGbits.ANSG8 = 0;
    TRISGbits.TRISG8 = 0;
    CNENGbits.CNIEG8 = 0;
}