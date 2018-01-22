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

#define LED_1 0 //PB8
#define LED_2 1
#define LED_3 2
#define LED_4 3 //PB11

#define BUTTON_T0 4 //PG12
#define BUTTON_T1 5
#define BUTTON_T2 6
#define BUTTON_T3 7 //PG15

#define INC_A 11
#define INC_B 12
#define INC_SW 13

#define HIGH 1
#define LOW 0

#ifdef	__cplusplus
extern "C" {
#endif

void initPin(uint16_t pin);
void digitalWrite(uint16_t pin, uint8_t mode);
void digitalWriteLEDs(uint16_t mask);
uint8_t digitalRead(uint16_t pin);
void initEncoder();
int8_t readEncoder();
void initPiezo();


#ifdef	__cplusplus
}
#endif

#endif	/* DIGITALIO_H */