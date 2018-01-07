#include <xc.h>

extern void EnSecOsc( void );

/******************************************************************************
 * Function:        Init_Timer1()
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is used to configure Timer1.
 *****************************************************************************/
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

/*******************************************************************************
 End of File
*/
