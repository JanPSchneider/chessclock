#include <xc.h>
#include <stdint.h>

// *****************************************************************************
// *****************************************************************************
// Section: File Scope or Global Constants
// *****************************************************************************
// *****************************************************************************
volatile uint8_t    hours;
volatile uint8_t    minutes;
volatile uint8_t    seconds;
volatile uint8_t    rtc_Lcd_Update;

/******************************************************************************
 * Function:        _T1Interrupt
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Timer1 Interrupt Handler.
 *****************************************************************************/
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