/** 
 * @file   digitalIo.c
 * @author Mongo le Otto
 *
 * @date 11.12.2017
 * 
 * @brief PIN activation and configuration
 */



// Check for Project Settings
#ifndef __dsPIC33EP512MU810__
    #error "Wrong Controller"
#endif

/* ***********************
 * Includes
 * ***********************
 */

#include "myxc.h"
#include <stdint.h>     //Standard typedefs
#include <stdbool.h>


/* ***********************
 * Defines
 * ***********************
 */

/* Substitute for stdlib.h */
#define	EXIT_SUCCESS	0
#define	EXIT_FAILURE	1

/* Hardware  */
#define _LED200 LATBbits.LATB8

/* ***********************
 * Prototypes
 * ***********************
 */

void delay_ms(uint16_t u16milliseconds);

/* ***********************
 * Main
 * ***********************
 */
int main() {

    /* Port Configurations */
    // DS70616G-page 209
    // ODCB (open drain config) unimplemented (DS70616G, Table 4-56)
    ANSELBbits.ANSB8=0;     //Digital I/O
    CNENBbits.CNIEB8=0;     //Disable change notification interrupt
    CNPUBbits.CNPUB8=0;     //Disable weak pullup
    CNPDBbits.CNPDB8=0;     //Disable weak pulldown
    TRISBbits.TRISB8=0;     //Pin B8: Digital Output
    LATBbits.LATB8=0;       //Pin B8: Low

    /* Endless Loop */
    while(1){
        /* LATBbits.LATB8 = !(LATBbits.LATB8); //Toggle Pin B8 */
        _LED200=!_LED200; //Toggle LED
        delay_ms(500);
    }//while
    
    return (EXIT_SUCCESS);  //never reached
} //main()


