#include <stdint.h>
#ifdef __cplusplus      // Provide C++ Compatability
extern "C"
{
    #endif

    /* variables used in Timer 1 ISR */
    extern volatile uint8_t hours;
    extern volatile uint8_t minutes;
    extern volatile uint8_t seconds;
    extern volatile uint8_t hourss;
    extern volatile uint8_t minutess;
    extern volatile uint8_t secondss;
    extern volatile uint8_t status;
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
