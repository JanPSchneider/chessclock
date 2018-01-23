/** 
 * @file  time.c
 * @author Tobias Haag, Felix Süß, Jan Schneider, Marcus Schoch
 * 
 * @brief 
 * 
 * @date 11.12.2017
 */

#include "time.h"

/** 
 * @brief Provides ms delay
 * @param ms Delay in milliseconds
 * @pre 7.37 PrimaryMHz (Internal Fast RC), e. g.: <br>
 * _FOSCSEL(FNOSC_FRC); //Initial Oscillator:  Internal Fast RC <br>
 * _FOSC(POSCMD_NONE);  //Primary Oscillator disabled (quartz not used) <br>
 * s. 7.37 MHz DS70216C-page 39-19 <br>
 * @attention Code has to be changed if a different oscillator frequency is used.
 */
void delay_ms(uint16_t ms){
    __delay_ms(ms);
}

/** 
 * @brief Legt einen Sound(Feedback) fest und die möglichkeit den Sound zu deaktivieren bzw zu aktivieren.
 * @param ms, frequency
 */
void feedback(uint16_t ms, uint16_t frequency, uint8_t muted) {
    ms /= 10; // Only 10ms duration steps for higher frequency resolution
    
    uint32_t cycles = (FCY/frequency)/2;
    
    if(muted == 1){
        
        while (ms) {
            int i;
            for (i = 0; i < frequency/100; i++) { 
                __delay32(cycles);
                LATGbits.LATG8 = 0;
            }
            ms--;
        }
    }
    else{   
        while (ms) {
            int i;
            for (i = 0; i < frequency/100; i++) { 
                __delay32(cycles);
                LATGbits.LATG8 = 1;
                __delay32(cycles);
                LATGbits.LATG8 = 0;
            }
            ms--;
        }
    }

}

/** 
 * @brief Initialisiert den TImer. Legt Bits für den Timer fest.
 * @attention Timer braucht 16 bits.
 */
void initTimer(){
    T1CONbits.TON = 0; // Enable Timer
    T1CONbits.TCS = 0; // Select internal instruction cycle clock
    T1CONbits.TGATE = 0; // Disable Gated Timer mode
    T1CONbits.TCKPS = 0b10; // Select 1:64 Prescaler
    TMR1 = 0x00; // Clear timer register
    PR1 = 62500; // Load the period value
    IFS0bits.T1IF = 0; // Clear Timer 1 Interrupt Flag
    T1CONbits.TON = 1; // Start Timer
}