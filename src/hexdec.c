#include <xc.h>
#include <stdint.h>

// *****************************************************************************
// *****************************************************************************
// Section: File Scope or Global Constants
// *****************************************************************************
// *****************************************************************************
volatile uint8_t    tens;
volatile uint8_t    ones;

/******************************************************************************
 * Function:        HexDec()
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:       This function is used to convert a hexadecimal number to its
 *                 decimal equivalent.
 *****************************************************************************/
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
