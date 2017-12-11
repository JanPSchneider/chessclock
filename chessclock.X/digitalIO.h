/* 
 * File:   digitalIO.h
 * Author: ICH, nicht Thomas
 *
 * Created on 11. Dezember 2017, 13:59
 */

#ifndef DIGITALIO_H
#define	DIGITALIO_H

#ifdef	__cplusplus
extern "C" {
#endif

    
    /* Port Configurations */
    // DS70616G-page 209
    // ODCB (open drain config) unimplemented (DS70616G, Table 4-56)
    ANSELBbits.ANSB8=0;     //Digital I/O
    CNENBbits.CNIEB8=0;     //Disable change notification interrupt
    CNPUBbits.CNPUB8=0;     //Disable weak pullup
    CNPDBbits.CNPDB8=0;     //Disable weak pulldown
    TRISBbits.TRISB8=0;     //Pin B8: Digital Output
    LATBbits.LATB8=0;       //Pin B8: Low


#ifdef	__cplusplus
}
#endif

#endif	/* DIGITALIO_H */

