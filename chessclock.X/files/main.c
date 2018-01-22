/**
 * @file  main.c
 * @author Tobias Haag, Felix Süß, Jan Schneider, Marcus Schoch
 * 
 * @brief Erstellung von Funktionen. Beispielsweise Menü und Einstellungen
 * 
 * @date 11.12.2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <p33EP512MU810.h>
#include "myxc.h"

#include "digitalIO.h"
#include "time.h"
#include "lcd.h"

#define MIN_TIME 60 // Sekunden
#define MAX_TIME 5400 // 90 Minuten in Sekunden angegeben
#define INIT_TIME 180 // Sekunden
#define EXTRA_TIME 0 // Sekunden
#define MAX_EXTRA_TIME 60 // Sekunden
#define SCROLLING 0

uint16_t initTime = INIT_TIME;
int16_t extra_time = EXTRA_TIME;
int16_t scrolls2 = SCROLLING;

uint16_t playertwo_sec = INIT_TIME, playerone_sec = INIT_TIME;
uint16_t playerone_turns = 0, playertwo_turns = 0;
bool playertwo_turn = false, playerone_turn = false;

/** 
 * @brief switch LEDs
 * @param change
 * @pre Switching the leds that are shining
 * @attention !!!
 */
void changeLED(bool change) {
    feedback(50, 1000);
    int i;
    if(change) {
        for (i = 3; i <= 3; i++) {
            digitalWriteLEDs(1 << i);
            delay_ms(50);
        }        
    } else {
        for (i = 0; i >= 0; i--) {
            digitalWriteLEDs(1 << i);
            delay_ms(50);
        } 
    }
}

/** 
 * @brief show start screen
 * @param -
 * @pre Showing "Welcome to CHESSCLOCK"
 * @attention if letters are changed change length of string
 */
void initialization() {
    LCD_PutString("Welcome to  ", 16);
    LCD_setPosition(1, 0);
    LCD_PutString("CHESSCLOCK", 16);
    
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH); 
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);
    changeLED(false);
}

/** 
 * @brief open time setting
 * @param -
 * @pre open the setting to change the game length
 * @attention !!!
 */
void openTimeSetting() {
    while(digitalRead(INC_SW)) {
        LCD_ClearScreen();
        char buffer[16];
        sprintf(buffer, "Set Time: %02d min", initTime/60);
        LCD_PutString(buffer, 16);
        
        initTime += readEncoder()*60;
        
        if(initTime < MIN_TIME) {
            initTime = MIN_TIME;
        } else if(initTime > MAX_TIME) {
            initTime = MAX_TIME;
        }        
    }
}

/** 
 * @brief bonus settings open
 * @param -
 * @pre !!!
 * @attention !!!
 */
void openBonusSetting() {
    while(digitalRead(INC_SW)) {
        LCD_ClearScreen();
        char buffer[16];
        sprintf(buffer, "Set Bonus: %2d s", extra_time);
        LCD_PutString(buffer, 16);
        
        extra_time += readEncoder();
        
        if(extra_time < 0) {
            extra_time = 0;
        } else if(extra_time > MAX_EXTRA_TIME) {
            extra_time = MAX_EXTRA_TIME;
        }       
    }
}

/** 
 * @brief open credits
 * @param -
 * @pre Shows students and Prof.
 * @attention !!!
 */
void openCredits() {
    LCD_ClearScreen();
    LCD_PutString("Created by: ", 16);
    LCD_setPosition(1,0);
    LCD_PutString("Students: ", 16);
    while(digitalRead(INC_SW)){
        scrolls2 += readEncoder();
        if(scrolls2 == 0){
            LCD_ClearScreen();
            LCD_PutString("Created by: ", 16);
            LCD_setPosition(1,0);
            LCD_PutString("Students: ", 16);
        }
        else if(scrolls2 == 1){
            LCD_ClearScreen();
            LCD_PutString("Students: ", 16);
            LCD_setPosition(1,0);
            LCD_PutString("Jan Schneider", 16);
        }
        else if(scrolls2 == 2){
            LCD_ClearScreen();
            LCD_PutString("Jan Schneider", 16);
            LCD_setPosition(1,0);
            LCD_PutString("Tobias Haag", 16);
       }
        else if(scrolls2 == 3){
            LCD_ClearScreen();
            LCD_PutString("Tobias Haag", 16);
            LCD_setPosition(1,0);
            LCD_PutString("Marcus Schoch", 16);
        }
        else if(scrolls2 == 4){
            LCD_ClearScreen();
            LCD_PutString("Marcus Schoch", 16);
            LCD_setPosition(1,0);
            LCD_PutString("Felix Suess", 16);
        }
        else if(scrolls2 == 5){
            LCD_ClearScreen();
            LCD_PutString("Felix Suess", 16);
            LCD_setPosition(1,0);
            LCD_PutString(" ", 16);
        }
        else if(scrolls2 == 6){
            LCD_ClearScreen();
            LCD_PutString(" ", 16);
            LCD_setPosition(1,0);
            LCD_PutString("Special Thanks ", 16);
        }
        else if(scrolls2 == 7){
            LCD_ClearScreen();
            LCD_PutString("Special Thanks ", 16);
            LCD_setPosition(1,0);
            LCD_PutString("to our Prof ", 16);
        }
        else if(scrolls2 == 8){
            LCD_ClearScreen();
            LCD_PutString("to our Prof ", 16);
            LCD_setPosition(1,0);
            LCD_PutString("Juergen Schuele ", 16);
        }
    }
}


/** 
 * @brief open menu
 * @param -
 * @pre !!!
 * @attention !!!
 */
void openMenu() {
    LCD_ClearScreen();
    LCD_PutString("Settings", 16);
    feedback(1000, 1000);
   
    int8_t firstLine;
    int8_t secondLine;
    int8_t thirdLine;
    int8_t scrolls1 = -1;
    while(digitalRead(INC_SW)) {
        scrolls1 += readEncoder();
        if (scrolls1 != 0) {                  
            if(scrolls1 == 1){
                LCD_ClearScreen();
                LCD_PutString("> Set total time", 16);
                LCD_PutString("  Set turn bonus", 16);                      
            }
            else if(scrolls1 == 2){
                LCD_ClearScreen();
                LCD_PutString("  Set total time\n", 16);
                LCD_PutString("> Set turn bonus", 16);
                                       
            }
            else if(scrolls1 == 3){
                   LCD_ClearScreen();
                   LCD_PutString("  Set turn bonus", 16);
                   LCD_setPosition(1,0);
                   LCD_PutString("> Credits", 16);
            }
        }                 
    }  
    firstLine = scrolls1 == 1;
    secondLine = scrolls1 == 2;
    thirdLine = scrolls1 == 3;
   
   feedback(1000, 1000);
   if (firstLine) {
       openTimeSetting();
   }
   else if(secondLine) {
       openBonusSetting();
   }
   else if(thirdLine) {
       openCredits();
   }   
   feedback(1000, 2000);    
}

/** 
 * @brief show time statistics
 * @param playerName, playerTime
 * @pre !!!
 * @attention !!!
 */
void showTimePlayedStats(char* playerName, uint16_t playerTime) {
    LCD_ClearScreen();
    LCD_PutString(playerName, 5); LCD_PutString(" used time:", 11);
    uint16_t used_sec = initTime - playerTime;
    char string[16];
    LCD_setPosition(1, 0);
    sprintf(string, "%02d:%02d min (%d%%)", used_sec/60, used_sec%60, used_sec*100/initTime);
    LCD_PutString(string, 16);
}

/** 
 * @brief show turns
 * @param playName, playerTime, turns
 * @pre !!!
 * @attention !!!
 */
void showStats(char* playerName, uint16_t playerTime, uint16_t turns) {
    LCD_ClearScreen();
    LCD_PutString(playerName, 5); LCD_PutString(" turns:", 11);
    uint16_t used_sec = initTime - playerTime;
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

/** 
 * @brief game over screen
 * @param -
 * @pre !!!
 * @attention !!!
 */
void showGameOver() {
    LCD_ClearScreen();
    LCD_PutString("## Game Over ##", 15);
    LCD_setPosition(1, 0);
    if(playerone_sec == 0) {
        LCD_PutString("Two Timeout!", 16);
    } else if(playertwo_sec == 0) {
        LCD_PutString("One Timeout!", 16);
    } else {
        LCD_PutString("   (in time)   ", 14);
    }    
}

/** 
 * @brief handle game over
 * @param -
 * @pre happens when game is over
 * @attention !!!
 */
void handleEnding() { 
    showGameOver();
    
    while(digitalRead(BUTTON_T2)) {
        Nop();
    }
    
    uint8_t i = 0;
    while (digitalRead(BUTTON_T1)) {
        if(!digitalRead(BUTTON_T2)) {
            switch(i) {
                case 0:
                  showTimePlayedStats("P One", playerone_sec);
                  break;
                case 1:
                  showTimePlayedStats("P Two", playertwo_sec);
                  break;
                case 2:
                  showStats("P one", playerone_sec, playerone_turns);
                  break;
                case 3:
                  showStats("P Two", playertwo_sec, playertwo_turns);
                  break;
            }
            i++;
            i %= 4; // Max 4 pages
            feedback(500, 1000);
        }
    }
    feedback(1000, 100);
}

/** 
 * @brief reset game
 * @param -
 * @pre !!!
 * @attention !!!
 */
void resetGame() {
    playerone_turn = false;
    playertwo_turn = false;
    playerone_sec = initTime;
    playertwo_sec = initTime;
    playerone_turns = 0;
    playertwo_turns = 0;
}

/** 
 * @brief show clock
 * @param -
 * @pre !!!
 * @attention !!!
 */
void showClock() {
    char string[16];
    LCD_ClearScreen();
    sprintf(string, "%2d.P One: %02d:%02d", playerone_turns, playerone_sec/60, playerone_sec%60);
    LCD_setPosition(0, 0);
    LCD_PutString(string, 16);
    sprintf(string, "%2d.P Two: %02d:%02d", playertwo_turns, playertwo_sec/60, playertwo_sec%60);
    LCD_setPosition(1, 0);
    LCD_PutString(string, 16);
}

/** 
 * @brief loop
 * @param -
 * @pre !!!
 * @attention !!!
 */
void loop() {    
    while(1) {
        
        while (IFS0bits.T1IF == 0) {
            if(!digitalRead(BUTTON_T0) && !playertwo_turn) {
                playertwo_turns++;
                playertwo_sec += extra_time;
                playertwo_turn = true;
                playerone_turn = false;
                showClock();
                changeLED(false);
            }
            if(!digitalRead(BUTTON_T3) && !playerone_turn) {
                playerone_turns++;
                playerone_sec += extra_time;
                playertwo_turn = false;
                playerone_turn = true;
                showClock();
                changeLED(true);
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
            
            if(playertwo_turn) {
                playertwo_sec--;
            } else if(playerone_turn) {
                playerone_sec--;
            } else {
                digitalWriteLEDs(0b0110);
            }
            
            // Stop game on timeout or manual button press
            if(playerone_sec == 0 || playertwo_sec == 0 || !digitalRead(BUTTON_T1)) {
                handleEnding();
                resetGame();
            }
        }
        
        showClock();
    }
}

/** 
 * @brief main
 * @param argc, argv
 * @pre main part of CHESSCLOCK to keep everything working
 * @attention only works if everything
 */
int main(int argc, char** argv) {
       
    initPin(LED_1);
    initPin(LED_2);
    initPin(LED_3);
    initPin(LED_4);    
    initPin(BUTTON_T0);
    initPin(BUTTON_T1);
    initPin(BUTTON_T2);
    initPin(BUTTON_T3);
    
    initEncoder();
    initTimer(); 
    initPiezo();    
    LCD_Initialize();
    
    initialization();

    loop();    
    
    return (EXIT_SUCCESS);
}