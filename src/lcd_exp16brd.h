#include <stdint.h>

#ifdef __cplusplus                      // Provide C++ Compatability
extern "C"
{
    #endif

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Routines
    // *****************************************************************************
    // *****************************************************************************
    /******    LCD FUNCTION PROTOYPES ******/
    void    Init_LCD( void );           // initialize display
    void    LCD_Cmd( int8_t cmd );      // write command to lcd
    void    LCD_Data( int8_t data );    // write data to lcd
    void    Puts_LCD( uint8_t *data, uint8_t count );

    // *****************************************************************************
    // *****************************************************************************
    // Section: Helper Macros
    // *****************************************************************************
    // *****************************************************************************

    /*****    LCD COMMAND FUCNTION PROTOTYPES  *****/
    #define cursor_right()  LCD_Cmd( 0x14 )
    #define cursor_left()   LCD_Cmd( 0x10 )
    #define display_shift() LCD_Cmd( 0x1C )
    #define home_clr()      LCD_Cmd( 0x01 )
    #define home_it()       LCD_Cmd( 0x02 )
    #define line_1()        LCD_Cmd( 0x00 )
    #define line_2()        LCD_Cmd( 0xC0 ) // (0xC0)
    #ifdef __cplusplus                      // Provide C++ Compatibility
}

#endif
