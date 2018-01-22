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
//    if (ms == 0) return;
//    uint16_t ui16_i=0;
//    while(ms){
//        for (ui16_i=0;ui16_i<331;ui16_i++){    //1 ms delay loop 331x4?
//            __asm__ volatile("nop \n\t"
//                             "nop \n\t"
//                             "nop \n\t"); //Nop();
//        }//for
//        ms--;
//    }//while
    __delay_ms(ms);

}

/** 
 * @brief !!!
 * @param us
 * @pre !!!
 * @attention !!!
 */
void delay_us(uint16_t us) {
    __delay_us(us);
}

/** 
 * @brief beeping
 * @param ms, freq
 * @pre !!!
 * @attention !!!
 */
void beep(uint16_t ms, uint16_t freq) {
    ms /= 10; // Only 10ms duration steps for higher freq resolution
    uint16_t freq_loop = freq/100; // 1/100 second to do in each loop
    uint32_t cycles = (FCY/freq)/2;
    
    while (ms) {
        int i;
        for (i = 0; i < freq_loop; i++) { 
            __delay32(cycles);
            LATGbits.LATG8 = 1;
            __delay32(cycles);
            LATGbits.LATG8 = 0;
        }
        ms--;
    }

}

/** 
 * @brief init timer 1
 * @param -
 * @pre initialise timer 1.
 * @attention timer 1 uses 16 Bit.
 */
void initT1(){
    T1CONbits.TON = 0; // Enable Timer
    T1CONbits.TCS = 0; // Select internal instruction cycle clock
    T1CONbits.TGATE = 0; // Disable Gated Timer mode
    T1CONbits.TCKPS = 0b10; // Select 1:64 Prescaler
    TMR1 = 0x00; // Clear timer register
    PR1 = 62500; // Load the period value
    IFS0bits.T1IF = 0; // Clear Timer 1 Interrupt Flag
    T1CONbits.TON = 1; // Start Timer
}