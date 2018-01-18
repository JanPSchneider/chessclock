/**
 * @file  melody.c
 * @author Tobias Haag, Felix Süß, Jan Schneider, Marcus Schoch
 * 
 * @brief FUnktion zum Abspielen der Startmelodie.
 * 
 * @date 11.12.2017
 */

#include "melodys.h"
#include "pitches.h"

#include "../time/time.h"

/** 
 * @brief playing start meoldie
 * @param -
 * @pre The melodie the board plays when it is started
 * @attention Totally annoying.
 */
void playStartMelody() {
    beep(500, NOTE_D6);
    beep(500, NOTE_D4);
    beep(500, NOTE_D6);
}

