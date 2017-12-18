/* 
 * File:   digitalIO.h
 * Author: ICH, nicht Thomas
 *
 * Created on 11. Dezember 2017, 13:59
 */

#ifndef DIGITALIO_H
#define	DIGITALIO_H
#define _LED200 LATBbits.LATB8
#define _LED201 LATBbits.LATB9
#define _LED202 LATBbits.LATB10
#define _LED203 LATBbits-LATB11


#ifndef __dsPIC33EP512MU810__
    #error "Wrong Controller"
#endif
    

#include <stdint.h>


int pin;
int status;

// common rtc
#ifdef __cplusplus      // Provide C++ Compatability
extern "C"
{
    #endif

    /* variables used in Timer 1 ISR */
    extern volatile uint8_t hours;
    extern volatile uint8_t minutes;
    extern volatile uint8_t seconds;
    extern volatile uint8_t rtc_Lcd_Update;

    /* variables used in hex to decimal routine */
    extern volatile uint8_t hunds;
    extern volatile uint8_t tens;
    extern volatile uint8_t ones;

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Routines
    // *****************************************************************************
    // *****************************************************************************
    extern void             HexDec( uint8_t count );
    extern void             Init_Timer1( void );
    extern void             Init_INTpin( void );

    #ifdef __cplusplus  // Provide C++ Compatibility
}

#endif

// delay
    #ifdef __cplusplus      // Provide C++ Compatability
extern "C"
{
        #endif

    // Section: Constants
        #define Delay200uS_count    200
        #define Delay_1mS_Cnt       1
        #define Delay_2mS_Cnt       2
        #define Delay_5mS_Cnt       5
        #define Delay_15mS_Cnt      15
        #define Delay_1S_Cnt        1000

    // Section: Interface Routines
    void    Delay( uint16_t delay_count );
    void    Delay_Us( uint16_t delayUs_count );

        #ifdef __cplusplus  // Provide C++ Compatibility
}

    #endif
#endif

// lcd display
#ifdef __cplusplus                      // Provide C++ Compatability
extern "C"
{
    #endif

    // Section: Interface Routines
    /******    LCD FUNCTION PROTOYPES ******/
    void    Init_LCD( void );           // initialize display
    void    LCD_Cmd( int8_t cmd );      // write command to lcd
    void    LCD_Data( int8_t data );    // write data to lcd
    void    Puts_LCD( uint8_t *data, uint8_t count );

    // Section: Helper Macros

    /*****    LCD COMMAND FUCNTION PROTOTYPES  *****/
    #define cursor_right()  LCD_Cmd( 0x14 )
    #define cursor_left()   LCD_Cmd( 0x10 )
    #define display_shift() LCD_Cmd( 0x1C )
    #define home_clr()      LCD_Cmd( 0x01 )
    #define home_it()       LCD_Cmd( 0x02 )
    #define line_2()        LCD_Cmd( 0xC0 ) // (0xC0)
    #ifdef __cplusplus                      // Provide C++ Compatibility
}

#endif



//void ledActivationAndConfiguration(pin, status){ 
   
//    if(status<=1 && status >=0){
        
        /* Port Configuration LED 200 */
//        if(pin == _LED200){
//        ANSELBbits.ANSB8=0;     //Digital I/O
//        CNENBbits.CNIEB8=0;     //Disable change notification interrupt
//        CNPUBbits.CNPUB8=0;     //Disable weak pullup
//        CNPDBbits.CNPDB8=0;     //Disable weak pulldown
//        TRISBbits.TRISB8=0;     //Pin B8: Digital Output
//        LATBbits.LATB8=status;       //Pin B8: Low
//        }

        /* Port Configuration LED 201 */
//        if(pin == _LED201){
//        ANSELBbits.ANSB9=0;     //Digital I/O
//        CNENBbits.CNIEB9=0;     //Disable change notification interrupt
//        CNPUBbits.CNPUB9=0;     //Disable weak pullup
//        CNPDBbits.CNPDB9=0;     //Disable weak pulldown
//        TRISBbits.TRISB9=0;     //Pin B8: Digital Output
//        LATBbits.LATB9=status;       //Pin B8: Low
//        }

        /* Port Configuration LED 202 */
//        if(pin == _LED202){
//        ANSELBbits.ANSB10=0;     //Digital I/O
//        CNENBbits.CNIEB10=0;     //Disable change notification interrupt
//        CNPUBbits.CNPUB10=0;     //Disable weak pullup
//        CNPDBbits.CNPDB10=0;     //Disable weak pulldown
//        TRISBbits.TRISB10=0;     //Pin B8: Digital Output
//        LATBbits.LATB10=status;       //Pin B8: Low
//        }

        /* Port Configuration LED 203 */
 //       if(pin == _LED203){
//        ANSELBbits.ANSB11=0;     //Digital I/O
//        CNENBbits.CNIEB11=0;     //Disable change notification interrupt
//        CNPUBbits.CNPUB11=0;     //Disable weak pullup
//        CNPDBbits.CNPDB11=0;     //Disable weak pulldown
//        TRISBbits.TRISB11=0;     //Pin B8: Digital Output
//        LATBbits.LATB11=status;       //Pin B8: Low
//        }
//    }
   
//}    
#ifdef	__cplusplus
}
#endif

