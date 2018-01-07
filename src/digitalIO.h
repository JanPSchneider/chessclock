/* 
 * File:   digitalIO.h
 * Author: ICH
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
    
int pin;
int status;

// common rtc
#ifdef __cplusplus      // Provide C++ Compatability
extern "C"
{
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
}
#endif

