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

#include <stdint.h>     //Standard typedefs
#include <stdbool.h>
#include "digitalIO.h"

/* ***********************
 * Defines
 * ***********************
 */

/* Substitute for stdlib.h */
#define	EXIT_SUCCESS	0
#define	EXIT_FAILURE	1

/* Hardware  */

#define _SW201 LATBbits.RG13

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

    /* Endless Loop */
    while(1){
        /* LATBbits.LATB8 = !(LATBbits.LATB8); //Toggle Pin B8 */
        ledActivationAndConfiguration(_LED200,1);
        ledActivationAndConfiguration(_LED201,1);
        ledActivationAndConfiguration(_LED202,1);
        ledActivationAndConfiguration(_LED203,1);
        delay_ms(500);
        ledActivationAndConfiguration(_LED200,0);
        ledActivationAndConfiguration(_LED201,0);
        ledActivationAndConfiguration(_LED202,0);
        ledActivationAndConfiguration(_LED203,0);
        delay_ms(500);
    }//while
    
    return (EXIT_SUCCESS);  //never reached
}