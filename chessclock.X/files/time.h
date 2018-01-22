/* 
 * @file  time.h
 * @author Tobias Haag, Felix Süß, Jan Schneider, Marcus Schoch
 * 
 * @brief Erstellung einer Zeiteinheit mithilfe der CPU Frequenz
 * 
 * @date 11.12.2017
 */
#include <stdint.h>
#include <p33EP512MU810.h>

#define FCY  4000000UL // CPU Frequenz für Verzögerungen
#include <libpic30.h>

void delay_ms(uint16_t ms);
void feedback(uint16_t ms, uint16_t frequency, uint8_t muted);
void initTimer();