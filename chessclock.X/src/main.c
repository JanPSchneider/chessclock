/**
 * @file  main.c
 * @author Tobias Haag, Felix Süß, Jan Schneider, Marcus Schoch
 * 
 * @brief Erstellung von Funktionen. Beispielsweise Menü und Einstellungen
 * 
 * @date Created on 16.01.2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <p33EP512MU810.h>
#include "myxc.h"

#include "io/digitalIO.h"
#include "time/time.h"
#include "lcd/lcd.h"
#include "sound/melodys.h"

#define MIN_TIME_S 60
#define MAX_TIME_S 5400 // 90 min
#define INIT_TIME_S 180
#define TURN_BONUS 0
#define MAX_TURN_BONUS 60

uint16_t initalTime = INIT_TIME_S;
int16_t turn_bonus = TURN_BONUS;

uint16_t white_sec = INIT_TIME_S, black_sec = INIT_TIME_S;
uint16_t white_turns = 0, black_turns = 0;
bool white_turn = false, black_turn = false;

void doLEDSwitch(bool dir) {
    beep(50, 1000);
    int i;
    if(dir) {
        for (i = 0; i <= 3; i++) {
            digitalWriteLEDs(1 << i);
            delay_ms(50);
        }        
    } else {
        for (i = 3; i >= 0; i--) {
            digitalWriteLEDs(1 << i);
            delay_ms(50);
        } 
    }
}

void startSequence() {
    LCD_PutString("Welcome to  ", 16);
    LCD_setPosition(1, 0);
    LCD_PutString("CHESSCLOCK", 16);
    
    digitalWrite(LED200, HIGH);
    beep(1000, 250);
    digitalWrite(LED201, HIGH);
    beep(1000, 500);   
    digitalWrite(LED202, HIGH);
    beep(1000, 1000);
    digitalWrite(LED203, HIGH);
    doLEDSwitch(false);
}

void openTimeSetting() {
    while(digitalRead(INC_SW)) {
        LCD_ClearScreen();
        char buffer[16];
        sprintf(buffer, "Set Time: %02d min", initalTime/60);
        LCD_PutString(buffer, 16);
        
        initalTime += readEncoderPulse()*60;
        
        if(initalTime < MIN_TIME_S) {
            initalTime = MIN_TIME_S;
        } else if(initalTime > MAX_TIME_S) {
            initalTime = MAX_TIME_S;
        }        
    }
}

void openBonusSetting() {
    while(digitalRead(INC_SW)) {
        LCD_ClearScreen();
        char buffer[16];
        sprintf(buffer, "Set Bonus: %2d s", turn_bonus);
        LCD_PutString(buffer, 16);
        
        turn_bonus += readEncoderPulse();
        
        if(turn_bonus < 0) {
            turn_bonus = 0;
        } else if(turn_bonus > MAX_TURN_BONUS) {
            turn_bonus = MAX_TURN_BONUS;
        }       
    }
}

void openMenu() {
    LCD_ClearScreen();
    LCD_PutString("Change Settings", 16);
    beep(1000, 1000);
    
    bool firstLine;
    int8_t pulse = -1; // Set to first line (-1 means backward rotation)
    while(digitalRead(INC_SW)) {
        if (pulse != 0) {
            firstLine = pulse < 0;
            LCD_ClearScreen();
            LCD_PutChar(firstLine? '>':' ');
            LCD_PutString("Set total time\n", 16);
            LCD_PutChar(firstLine? ' ':'>');
            LCD_PutString("Set turn bonus", 16);
        }        
        pulse = readEncoderPulse();
    }
    
    beep(1000, 1000);
    if (firstLine) {
        openTimeSetting();
    } else {
        openBonusSetting();
    }
    
    beep(1000, 2000);    
}



void showTimeStat(char* playerName, uint16_t playerTime) {
    LCD_ClearScreen();
    LCD_PutString(playerName, 5); LCD_PutString(" used time:", 11);
    uint16_t used_sec = initalTime - playerTime;
    char string[16];
    LCD_setPosition(1, 0);
    sprintf(string, "%02d:%02d min (%d%%)", used_sec/60, used_sec%60, used_sec*100/initalTime);
    LCD_PutString(string, 16);
}

void showAvgStat(char* playerName, uint16_t playerTime, uint16_t turns) {
    LCD_ClearScreen();
    LCD_PutString(playerName, 5); LCD_PutString(" turns:", 11);
    uint16_t used_sec = initalTime - playerTime;
    char string[16];
    LCD_setPosition(1, 0);
    if(turns > 0) {
        used_sec /= turns;
        sprintf(string, "AVG: %d s (x%d)", used_sec, turns);
        LCD_PutString(string, 16);
    } else {
        LCD_PutString("No turns made!", 14);
    }        
}

void showGameOver() {
    LCD_ClearScreen();
    LCD_PutString("## Game Over ##", 15);
    LCD_setPosition(1, 0);
    if(black_sec == 0) {
        LCD_PutString("Black Timeout!", 14);
    } else if(white_sec == 0) {
        LCD_PutString("White Timeout!", 14);
    } else {
        LCD_PutString("   (in time)   ", 14);
    }    
}

void handleEnding() { 
    showGameOver();
    
    while(digitalRead(SW200)) {
        Nop();
    }
    
    uint8_t i = 0;
    while (digitalRead(SW201)) {
        if(!digitalRead(SW200)) {
            switch(i) {
                case 0:
                  showTimeStat("Black", black_sec);
                  break;
                case 1:
                  showTimeStat("White", white_sec);
                  break;
                case 2:
                  showAvgStat("Black", black_sec, black_turns);
                  break;
                case 3:
                  showAvgStat("White", white_sec, white_turns);
                  break;
            }
            i++;
            i %= 4; // Max 4 pages
            beep(500, 1000);
        }
    }
    beep(1000, 100);
}

void resetGame() {
    black_turn = false;
    white_turn = false;
    black_sec = initalTime;
    white_sec = initalTime;
    black_turns = 0;
    white_turns = 0;
}

void showClock() {
    char string[16];
    LCD_ClearScreen();
    sprintf(string, "%2d.Black: %02d:%02d", black_turns, black_sec/60, black_sec%60);
    LCD_setPosition(0, 0);
    LCD_PutString(string, 16);
    sprintf(string, "%2d.White: %02d:%02d", white_turns, white_sec/60, white_sec%60);
    LCD_setPosition(1, 0);
    LCD_PutString(string, 16);
}

void loop() {    
    while(1) {
        
        while (IFS0bits.T1IF == 0) {
            if(!digitalRead(SW202) && !white_turn) {
                white_turns++;
                white_sec += turn_bonus;
                white_turn = true;
                black_turn = false;
                showClock();
                doLEDSwitch(false);
            }
            if(!digitalRead(SW203) && !black_turn) {
                black_turns++;
                black_sec += turn_bonus;
                white_turn = false;
                black_turn = true;
                showClock();
                doLEDSwitch(true);
            }
        }
        // Check if Timer overflowed
        if(IFS0bits.T1IF == 1){
            // reset Timer
            IFS0bits.T1IF = 0; 
            TMR1 = 0x00;
            PR1 = 62500; // 1 sec
            
            ClrWdt(); // Reset Watchdog
            
            if(!digitalRead(INC_SW)) { // Open Settings
                openMenu();                
                resetGame();
            }
            
            if(white_turn) {
                white_sec--;
            } else if(black_turn) {
                black_sec--;
            } else {
                digitalWriteLEDs(0b0110);
            }
            
            // Stop game on timeout or manual button press
            if(black_sec == 0 || white_sec == 0 || !digitalRead(SW201)) {
                handleEnding();
                resetGame();
            }
        }
        
        showClock();
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
       
    pinMode(LED200, OUTPUT);
    pinMode(LED201, OUTPUT);
    pinMode(LED202, OUTPUT);
    pinMode(LED203, OUTPUT);    
    pinMode(SW200, INPUT_PULLUP);
    pinMode(SW201, INPUT_PULLUP);
    pinMode(SW202, INPUT_PULLUP);
    pinMode(SW203, INPUT_PULLUP);
    
    initEncoder();
    initT1(); 
    initPiezo();    
    LCD_Initialize();
    
    //startSequence();
    playStartMelody();

    loop();    
    
    return (EXIT_SUCCESS);
}


