/* 
 * @file  digitalIO.h
 * @author Tobias Haag, Felix Suess, Jan Schneider, Marcus Schoch
 * 
 * @brief Definierung der LED's und Switches bzw. Buttons sowie dem Inkrementer
 * 
 * @date 11.12.2017
 */

#include <stdint.h>
#include <stdio.h>

#ifndef DIGITALIO_H
#define	DIGITALIO_H
#endif 

#define OUTPUT 0
#define INPUT 1
#define INPUT_PULLUP 2
#define INPUT_PULLDOWN 3

#define LED_1 0 //PB8
#define LED_2 1 //RB9
#define LED_3 2 //RB8
#define LED_4 3 //PB11

#define BUTTON_T0 4 //RG12
#define BUTTON_T1 5 //RG13
#define BUTTON_T2 6 //RG14
#define BUTTON_T3 7 //RG15

#define INC_A 11 //RG_0
#define INC_B 12 //RG_1
#define INC_SW 13 //RG_9

#define HIGH 1
#define LOW 0

void initPin(uint16_t pin);
void digitalWrite(uint16_t pin, uint8_t mode);
void digitalWriteLEDs(uint16_t overwrite);
uint8_t digitalRead(uint16_t pin);
void initEncoder();
int8_t readEncoder();
void initPiezo();