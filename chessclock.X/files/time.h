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

#define FCY  4000000UL // CPU Frequency for delays
#include <libpic30.h>

#ifndef TIME_H
#define	TIME_H

#ifdef	__cplusplus
extern "C" {
#endif

    void delay_ms(uint16_t ms);
    void delay_us(uint16_t us);
    void feedback(uint16_t ms, uint16_t freq, uint8_t muted);
    void initTimer();

#ifdef	__cplusplus
}
#endif

#endif	/* TIME_H */