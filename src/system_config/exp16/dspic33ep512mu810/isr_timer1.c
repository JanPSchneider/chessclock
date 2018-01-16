#include <xc.h>
#include <stdint.h>

// *****************************************************************************
// *****************************************************************************
// Section: File Scope or Global Constants
// *****************************************************************************
// *****************************************************************************
volatile uint8_t    hours;
volatile uint8_t    minutes = 5;
volatile uint8_t    seconds;
volatile uint8_t    hourss;
volatile uint8_t    minutess = 5;
volatile uint8_t    secondss;
volatile uint8_t    rtc_Lcd_Update;
volatile uint8_t    status;

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
    if(status == 0)
    {
        if( seconds > 0 )          // is cummulative seconds < 59?
        {
            seconds--;              // yes, so increment seconds
        }
        else                        // else seconds => 59
        {
            seconds = 0x3B;         // reset seconds
            if( minutes > 0 )      // is cummulative minutes < 59?
            {
                minutes--;          // yes, so updates minutes
            }
            else                    // else minutes => 59
            {
                minutes = 0x3B;     // reset minutes
                if( hours > 0 )    // is cummulative hours < 23
                {
                    hours--;        // yes, so update hours
                }
                else
                {
                    hours = 0x17;   // reset time
                }
            }
        }
    }
    else
    {
        if( secondss > 0 )          // is cummulative seconds < 59?
        {
            secondss--;              // yes, so increment seconds
        }
        else                        // else seconds => 59
        {
            secondss = 0x3B;         // reset seconds
            if( minutess > 0 )      // is cummulative minutes < 59?
            {
                minutess--;          // yes, so updates minutes
            }
            else                    // else minutes => 59
            {
                minutess = 0x3B;     // reset minutes
                if( hourss > 0 )    // is cummulative hours < 23
                {
                    hourss--;        // yes, so update hours
                }
                else
                {
                    hourss = 0x17;   // reset time
                }
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

void changeStatus(uint8_t setstatus)
{
    status = setstatus;
}