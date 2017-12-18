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
#include <xc.h>

/* ***********************
 * Defines
 * ***********************
 */

/* Substitute for stdlib.h */
#define	EXIT_SUCCESS	0
#define	EXIT_FAILURE	1

/* Hardware  */

#define _SW201 LATBbits.RG13

// Control signal data pins
#define RW  LATDbits.LATD5  // LCD R/W signal
#define RS  LATBbits.LATB15 // LCD RS signal
#define E   LATDbits.LATD4  // LCD E signal

// Control signal pin direction
#define RW_TRIS TRISDbits.TRISD5
#define RS_TRIS TRISBbits.TRISB15
#define E_TRIS  TRISDbits.TRISD4

// Data signals and pin direction
#define DATA        LATE    // Port for LCD data
#define DATAPORT    PORTE
#define TRISDATA    TRISE   // I/O setup for data Port

/* ***********************
 * Prototypes
 * ***********************
 */

void delay_ms(uint16_t u16milliseconds);

volatile uint8_t    hours;
volatile uint8_t    minutes;
volatile uint8_t    seconds;
volatile uint8_t    rtc_Lcd_Update;

volatile uint8_t    tens;
volatile uint8_t    ones;

void __attribute__ ( (__interrupt__) )  _OscillatorFail( void );
void __attribute__ ( (__interrupt__) )  _AddressError( void );
void __attribute__ ( (__interrupt__) )  _StackError( void );
void __attribute__ ( (__interrupt__) )  _MathError( void );
void __attribute__ ( (__interrupt__) )  _DMACError( void );

/* ***********************
 * Main
 * ***********************
 */
//int main() {

    /* Endless Loop */
//    while(1){
//        /* LATBbits.LATB8 = !(LATBbits.LATB8); //Toggle Pin B8 */
//        ledActivationAndConfiguration(_LED200,1);
//        ledActivationAndConfiguration(_LED201,1);
//        ledActivationAndConfiguration(_LED202,1);
//        ledActivationAndConfiguration(_LED203,1);
//        delay_ms(500);
//        ledActivationAndConfiguration(_LED200,0);
//        ledActivationAndConfiguration(_LED201,0);
//        ledActivationAndConfiguration(_LED202,0);
//        ledActivationAndConfiguration(_LED203,0);
//        delay_ms(500);
//    }//while
    
//    return (EXIT_SUCCESS);  //never reached
//}

// init timer1
extern void EnSecOsc( void );

void Init_Timer1( void )
{
    T1CON = 0;          // Timer reset
    IFS0bits.T1IF = 0;  // Reset Timer1 interrupt flag
    IPC0bits.T1IP = 4;  // Timer1 Interrupt priority level=4
    IEC0bits.T1IE = 1;  // Enable Timer1 interrupt
    PR1 = 0x8000;       // Timer1 period register = 32768
    T1CONbits.TCS = 1;  // Timer1 Clock= External
    EnSecOsc();         // Enable Secondary Osc
    T1CONbits.TON = 1;  // Enable Timer1 and start the counter
}

// set correct time (sec to min to hour, ...)
void __attribute__ ( (interrupt, no_auto_psv) ) _T1Interrupt( void )
{
    if( seconds < 59 )          // is cummulative seconds < 59?
    {
        seconds++;              // yes, so increment seconds
    }
    else                        // else seconds => 59
    {
        seconds = 0x00;         // reset seconds
        if( minutes < 59 )      // is cummulative minutes < 59?
        {
            minutes++;          // yes, so updates minutes
        }
        else                    // else minutes => 59
        {
            minutes = 0x00;     // reset minutes
            if( hours < 23 )    // is cummulative hours < 23
            {
                hours++;        // yes, so update hours
            }
            else
            {
                hours = 0x00;   // reset time
            }
        }
    }

    /* set flag to update LCD */
    rtc_Lcd_Update = 1;

    /* Toggle LED0 at 1 Hz rate */
    LATD = ( PORTD ^ 0x1 );

    /* reset Timer 1 interrupt flag */
    IFS0bits.T1IF = 0;
}

void Init_LCD( void )   // initialize LCD display
{
    // 15mS delay after Vdd reaches nnVdc before proceeding with LCD initialization
    // not always required and is based on system Vdd rise rate
    Delay( Delay_15mS_Cnt );        // 15ms delay

    /* set initial states for the data and control pins */
    LATE &= 0xFF00;
    RW = 0;                         // R/W state set low
    RS = 0;                         // RS state set low
    E = 0;                          // E state set low

    /* set data and control pins to outputs */
    TRISE &= 0xFF00;
    RW_TRIS = 0;                    // RW pin set as output
    RS_TRIS = 0;                    // RS pin set as output
    E_TRIS = 0;                     // E pin set as output

    /* 1st LCD initialization sequence */
    DATA &= 0xFF00;
    DATA |= 0x0038;
    E = 1;
    Nop();
    Nop();
    Nop();
    E = 0;                          // toggle E signal
    Delay( Delay_5mS_Cnt );         // 5ms delay

    /* 2nd LCD initialization sequence */
    DATA &= 0xFF00;
    DATA |= 0x0038;
    E = 1;
    Nop();
    Nop();
    Nop();
    E = 0;                          // toggle E signal
    Delay_Us( Delay200uS_count );   // 200uS delay

    /* 3rd LCD initialization sequence */
    DATA &= 0xFF00;
    DATA |= 0x0038;
    E = 1;
    Nop();
    Nop();
    Nop();
    E = 0;  // toggle E signal
    Delay_Us( Delay200uS_count );   // 200uS delay
    LCD_Cmd( 0x38 );                // function set
    LCD_Cmd( 0x0C );                // Display on/off control, cursor blink off (0x0C)
    LCD_Cmd( 0x06 );                // entry mode set (0x06)
}

/******************************************************************************
 * Function:        LCD_Cmd()
 *
 * PreCondition:    None
 *
 * Input:           cmd -> command to be sent
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:         This function serves as subroutiune for lcd commands
 *****************************************************************************/
void LCD_Cmd( int8_t cmd )  // subroutiune for lcd commands
{
    DATA &= 0xFF00;         // prepare RD0 - RD7
    DATA |= cmd;            // command byte to lcd
    RW = 0;                 // ensure RW is 0
    RS = 0;
    E = 1;                  // toggle E line
    Nop();
    Nop();
    Nop();
    E = 0;
    Delay( Delay_5mS_Cnt ); // 5ms delay
}

/******************************************************************************
 * Function:        LCD_Data
 *
 * PreCondition:    None
 *
 * Input:           data -> data to be sent
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:         This function serves as subroutiune for lcd data
 *****************************************************************************/
void LCD_Data( int8_t data )    // subroutine for lcd data
{
    RW = 0;         // ensure RW is 0
    RS = 1;         // assert register select to 1
    DATA &= 0xFF00; // prepare RD0 - RD7
    DATA |= data;   // data byte to lcd
    E = 1;
    Nop();
    Nop();
    Nop();
    E = 0;          // toggle E signal
    RS = 0;         // negate register select to 0
    Delay_Us( Delay200uS_count );   // 200uS delay
    Delay_Us( Delay200uS_count );   // 200uS delay
}

/******************************************************************************
 * Function:        Puts_LCD
 *
 * PreCondition:    None
 *
 * Input:           uint8_t *data, uint8_t count
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:         This function displays the data sent to LCD.
 *****************************************************************************/
void Puts_LCD( uint8_t *data, uint8_t count )
{
    while( count )
    {
        LCD_Data( *data++ );
        count--;
    }
}

void __attribute__ ( (interrupt, no_auto_psv) ) _OscillatorFail( void )
{
    INTCON1bits.OSCFAIL = 0;    //Clear the trap flag
    while( 1 );
}

void __attribute__ ( (interrupt, no_auto_psv) ) _AddressError( void )
{
    INTCON1bits.ADDRERR = 0;    //Clear the trap flag
    while( 1 );
}

void __attribute__ ( (interrupt, no_auto_psv) ) _StackError( void )
{
    INTCON1bits.STKERR = 0;     //Clear the trap flag
    while( 1 );
}

void __attribute__ ( (interrupt, no_auto_psv) ) _MathError( void )
{
    INTCON1bits.MATHERR = 0;    //Clear the trap flag
    while( 1 );
}

void __attribute__ ( (interrupt, no_auto_psv) ) _DMACError( void )
{
    INTCON1bits.DMACERR = 0;    //Clear the trap flag
    while( 1 );
}

// Converts a hex value to decimal.
void HexDec( int8_t count )
{
    tens = 0;           // initialize tens
    ones = 0;           // initialize ones
    while( count >= 10 )
    {
        count -= 10;    // subtract 10
        tens++;         // increment tens
    }

    ones = count;       // remaining count equals ones
}