/* 
 * @file  digitalIO.h
 * @author Tobias Haag, Felix Süß, Jan Schneider, Marcus Schoch
 * 
 * @brief Definierung der LED's und Switches bzw. Buttons sowie dem Incrementer
 * 
 * @date 11.12.2017
 */

#include <stdint.h>
#include <stdio.h>

#ifndef DIGITALIO_H
#define	DIGITALIO_H

#define OUTPUT 0
#define INPUT 1
#define INPUT_PULLUP 2
#define INPUT_PULLDOWN 3

#define LED200 0 //PB8
#define LED201 1
#define LED202 2
#define LED203 3 //PB11

#define SW200 4 //PG12
#define SW201 5
#define SW202 6
#define SW203 7 //PG15

#define INC_A 11
#define INC_B 12
#define INC_SW 13

#define HIGH 1
#define LOW 0

#ifdef	__cplusplus
extern "C" {
#endif

void pinInit(uint16_t pin);
void digitalWrite(uint16_t pin, uint8_t mode);
void digitalWriteLEDs(uint16_t mask);
uint8_t digitalRead(uint16_t pin);
void initEncoder();
int8_t readEncoderPulse();
void initPiezo();


#ifdef	__cplusplus
}
#endif

#endif	/* DIGITALIO_H */