/**
 * @file  main.c
 * @author Tobias Haag, Felix Süß, Jan Schneider, Marcus Schoch
 * 
 * @brief Erstellung von Funktionen und Hauptdatei von CHESSCLOCK. Beispielsweise Menü und Einstellungen.
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
#define TURNS 30 // Zugzahl
#define TURNS_MAX 50 // Maximale Zuganzahl
#define TURNS_MIN 2 // Minimale Zuganzahl
#define SCROLLING 0

uint16_t initTime = INIT_TIME;
uint16_t turns = TURNS;
int16_t extraTime = EXTRA_TIME;
int16_t scrolls3 = SCROLLING;

uint16_t playertwo_sec = INIT_TIME, playerone_sec = INIT_TIME;
uint16_t playerone_turns = 0, playertwo_turns = 0;
bool playertwo_turn = false, playerone_turn = false;
uint8_t mutedStatus = 0;

/** 
 * @brief LEDs umschalten
 * @param change
 */
void changeLED(bool change)
{
    feedback(50, 800, mutedStatus);
    int i;
    if (change) { // von rechts nach links
        for (i = 8; i <= 11; i++) {
            digitalWriteLEDs(1 << i);
            delay_ms(50);
        }
    }
    else { // von links nach rechts
        for (i = 11; i >= 8; i--) {
            digitalWriteLEDs(1 << i);
            delay_ms(50);
        }
    }
}

/** 
 * @brief Anzeige des Start Screens und LED-Startsequenz
 * @attention Wenn die Wortlänge geändert wird, muss die Länge des Stings geändert werden.
 */
void initialization()
{
    LCD_PutString("Welcome to  ", 16);
    LCD_setPosition(1, 0);
    LCD_PutString("CHESSCLOCK", 16);

    changeLED(true);
    changeLED(false);
}

/** 
 * @brief Öffnet die Einstellungen um die Länge des Spiels zu ändern.
 * @attention Maximale Spielzeit beträgt 90 Minuten.
 */
void timeSetting()
{
    while (digitalRead(INC_SW)) {
        LCD_ClearScreen();
        char buffer[16];
        sprintf(buffer, "Set Time: %02d min", initTime / 60); //02: minimale Länge von 2 Chars, d: signed decimal integer
        LCD_PutString(buffer, 16);

        initTime += readEncoder()*60;

        if (initTime < MIN_TIME) {
            initTime = MIN_TIME;
        }
        else if (initTime > MAX_TIME) {
            initTime = MAX_TIME;
        }
    }
}

void turnSetting()
{
    while (digitalRead(INC_SW)){
        LCD_ClearScreen();
        char buffer[16];
        sprintf(buffer, "Set Turns: %02d ", turns); //02: minimale Länge von 2 Chars, d: signed decimal integer
        LCD_PutString(buffer, 16);
        char string[16];
        sprintf(string, "min: %02d max: %02d", TURNS_MIN, TURNS_MAX);
        LCD_setPosition(1, 0);
        LCD_PutString(string, 16);
        
        turns += readEncoder();
        
        if(turns < TURNS_MIN){
            turns = TURNS_MAX;
        }
        else if(turns > TURNS_MAX){
            turns = TURNS_MIN;
        }
        
        
    }
}

/** 
 * @brief Öffnet die Einstellung Zusatzzeit je Zug einzustellen.
 * @attention Maximale Bonus Zeit beträgt 60 Sekunden
 */
void bonusSetting()
{
    while (digitalRead(INC_SW)) {
        LCD_ClearScreen();
        char buffer[16];
        sprintf(buffer, "Set Bonus: %2d s", extraTime);
        LCD_PutString(buffer, 16);

        extraTime += readEncoder();

        if (extraTime < 0) {
            extraTime = 0;
        }
        else if (extraTime > MAX_EXTRA_TIME) {
            extraTime = MAX_EXTRA_TIME;
        }
    }
}

/** 
 * @brief Öffnet die Credits: Studenten & Professor.
 */
void credits()
{
    LCD_ClearScreen();
    LCD_PutString("Created by: ", 16);
    LCD_setPosition(1, 0);
    LCD_PutString("Students: ", 16);
    while (digitalRead(INC_SW)) {
        scrolls3 += readEncoder();
        if (scrolls3 == 0) {
            LCD_ClearScreen();
            LCD_PutString("Created by: ", 16);
            LCD_setPosition(1, 0);
            LCD_PutString("Students: ", 16);
        }
        else if (scrolls3 == 1) {
            LCD_ClearScreen();
            LCD_PutString("Students: ", 16);
            LCD_setPosition(1, 0);
            LCD_PutString("Tobias Haag", 16);
        }
        else if (scrolls3 == 2) {
            LCD_ClearScreen();
            LCD_PutString("Tobias Haag", 16);
            LCD_setPosition(1, 0);
            LCD_PutString("Jan Schneider", 16);
        }
        else if (scrolls3 == 3) {
            LCD_ClearScreen();
            LCD_PutString("Jan Schneider", 16);
            LCD_setPosition(1, 0);
            LCD_PutString("Marcus Schoch", 16);
        }
        else if (scrolls3 == 4) {
            LCD_ClearScreen();
            LCD_PutString("Marcus Schoch", 16);
            LCD_setPosition(1, 0);
            LCD_PutString("Felix Suess", 16);
        }
        else if (scrolls3 == 5) {
            LCD_ClearScreen();
            LCD_PutString("Felix Suess", 16);
            LCD_setPosition(1, 0);
            LCD_PutString(" ", 16);
        }
        else if (scrolls3 == 6) {
            LCD_ClearScreen();
            LCD_PutString(" ", 16);
            LCD_setPosition(1, 0);
            LCD_PutString("Special Thanks ", 16);
        }
        else if (scrolls3 == 7) {
            LCD_ClearScreen();
            LCD_PutString("Special Thanks ", 16);
            LCD_setPosition(1, 0);
            LCD_PutString("to our Prof ", 16);
        }
        else if (scrolls3 == 8) {
            LCD_ClearScreen();
            LCD_PutString("to our Prof ", 16);
            LCD_setPosition(1, 0);
            LCD_PutString("Juergen Schuele ", 16);
        }
    }   
}

/** 
 * @brief Schaltet Feedback Töne ein oder aus.
 * @attention Es wird eventuell schwieriger die Schachuhr zu bedienen.
 */
void muted()
{
    if (mutedStatus == 1) {
        mutedStatus = 0;
    }
    else {
        mutedStatus = 1;
    }
}

/** 
 * @brief  Öffnet das Menü um Einstellungen vorzunehmen, sowie die Sounds an und aus zuschalten und die Credits anzusehen.
 */
void openMenu()
{
    LCD_ClearScreen();
    LCD_PutString("Settings", 16);
    feedback(1000, 800, mutedStatus);

    int8_t firstLine;
    int8_t secondLine;
    int8_t thirdLine;
    int8_t fourthLine;
    int8_t fifthLine;
    int8_t scrolls1 = -1;
    int8_t scrolls2 = scrolls1 - 1;
    while (digitalRead(INC_SW)) {
        scrolls1 += readEncoder();
        if (scrolls1 != 0) {
            if (scrolls1 == 1 && scrolls1 > scrolls2) {
                LCD_ClearScreen();
                LCD_PutString("> Set total time\n", 16);
                LCD_PutString("  Set turn bonus", 16);
            }
            else if (scrolls1 == 2 && scrolls1 > scrolls2) {
                LCD_ClearScreen();
                LCD_PutString("  Set total time\n", 16);
                LCD_PutString("> Set turns ", 16);

            }
            else if (scrolls1 == 3 && scrolls1 > scrolls2) {
                LCD_ClearScreen();
                LCD_PutString("  Set turns\n", 16);
                LCD_PutString("> Set turn bonus", 16);

            }
            else if (scrolls1 == 4 && scrolls1 > scrolls2) {
                LCD_ClearScreen();
                LCD_PutString("  Set turn bonus\n", 16);
                LCD_setPosition(1, 0);
                LCD_PutString("> Sounds On/Off", 16);
            }
            else if (scrolls1 >= 5 && scrolls1 > scrolls2) {
                LCD_ClearScreen();
                LCD_PutString("  Sounds On/Off\n", 16);
                LCD_setPosition(1, 0);
                LCD_PutString("> Credits", 16);
            }
            else if (scrolls1 == 4 && scrolls1 < scrolls2) {
                LCD_ClearScreen();
                LCD_PutString("> Sounds On/Off\n", 16);
                LCD_setPosition(1, 0);
                LCD_PutString("  Credits", 16);
            }
            else if (scrolls1 == 3 && scrolls1 < scrolls2) {
                LCD_ClearScreen();
                LCD_PutString("> Set turn bonus\n", 16);
                LCD_setPosition(1, 0);
                LCD_PutString("  Sounds On/Off", 16);
            }
            else if (scrolls1 == 2 && scrolls1 > scrolls2) {
                LCD_ClearScreen();
                LCD_PutString("> Set turns\n", 16);
                LCD_PutString("  Set turn bonus ", 16);

            }
            else if (scrolls1 == 1 && scrolls1 < scrolls2) {
                LCD_ClearScreen();
                LCD_PutString("> Set total time\n", 16);
                LCD_setPosition(1, 0);
                LCD_PutString("  Set turns ", 16);
            }
            else if (scrolls1 >= 5) {
                scrolls1 = 5;
            }
            else if (scrolls1 <= 0) {
                scrolls1 = 1;
            }
            if (scrolls2 != scrolls1) {
                scrolls2 = scrolls1;
            }
        }
    }
    firstLine = scrolls1 == 1;
    secondLine = scrolls1 == 2;
    thirdLine = scrolls1 == 3;
    fourthLine = scrolls1 == 4;
    fifthLine = scrolls1 >= 5;

    feedback(1000, 800, mutedStatus);

    if (firstLine) {
        timeSetting();
    }
    else if(secondLine){
        turnSetting();
    }
    else if (thirdLine) {
        bonusSetting();
    }
    else if (fourthLine) {
        muted();
    }
    else if (fifthLine) {
        credits();
    }

    feedback(1000, 1200, mutedStatus);
}

/** 
 * @brief Zeigt die pro Spieler gebrauchte Zeit an.
 * @param playerName, playerTime
 */
void showTimePlayedStats(char* playerName, uint16_t playerTime)
{
    LCD_ClearScreen();
    LCD_PutString(playerName, 5);
    LCD_PutString(" used time:", 11);
    uint16_t used_sec = initTime - playerTime;
    char string[16];
    LCD_setPosition(1, 0);
    sprintf(string, "%02d:%02d min (%d%%)", used_sec / 60, used_sec % 60, used_sec * 100 / initTime);
    LCD_PutString(string, 16);
}

/** 
 * @brief "Game Over" Screen. Kann durch Tastendruck bei einem Sieg hervorgerufen werden oder öffnet sich wenn die Zeit eines Spielers abgelaufen ist.
 */
void showGameOver()
{
    LCD_ClearScreen();
    LCD_PutString("   Game Over ", 15);
    LCD_setPosition(1, 0);
    if (playerone_sec == 0) {
        LCD_PutString("One Timeout!", 16);
    }
    else if (playertwo_sec == 0) {
        LCD_PutString("Two Timeout!", 16);
    }
    else if (playerone_turns >=  turns && playertwo_turns >= turns) {
        LCD_PutString(" No Turns Left", 16);
    }
    else {
        LCD_PutString("    in time    ", 14);
    }
}

/** 
 * @brief Definiert was nach einem "Game Over" passiert. Es kann hier nun durch Tastendruck T2 die Statistiken aufgerufen werden
 */
void handleEnding()
{
    showGameOver();

    while (digitalRead(BUTTON_T2)) {
        Nop();
    }

    uint8_t i = 0;
    while (digitalRead(BUTTON_T1)) {
        if (!digitalRead(BUTTON_T2)) {
            switch (i) {
            case 0:
                showTimePlayedStats("P One", playerone_sec);
                break;
            case 1:
                showTimePlayedStats("P Two", playertwo_sec);
                break;
            default: // falls der Code nicht wie gewollt funktioniert
                LCD_ClearScreen();
                LCD_PutString("! handleEnding", 16);
                delay_ms(1000);
                break;
            }
            i++;
            i %= 2; // maximal zwei Meldungen

            feedback(500, 800, mutedStatus);
        }
    }
    feedback(1000, 150, mutedStatus);

}

/** 
 * @brief Setzt das Spiel auf die Standard Werte zurück.
 */
void resetGame()
{
    playerone_turn = false;
    playertwo_turn = false;
    playerone_sec = initTime;
    playertwo_sec = initTime;
    playerone_turns = 0;
    playertwo_turns = 0;
}

/** 
 * @brief Zeigt die verbleibende Zeit der Spieler an
 */
void showClock()
{
    char string[16];
    LCD_ClearScreen();
    sprintf(string, "%2d.P One: %02d:%02d", playerone_turns, playerone_sec / 60, playerone_sec % 60);
    LCD_setPosition(0, 0);
    LCD_PutString(string, 16);
    sprintf(string, "%2d.P Two: %02d:%02d", playertwo_turns, playertwo_sec / 60, playertwo_sec % 60);
    LCD_setPosition(1, 0);
    LCD_PutString(string, 16);
}

/** 
 * @brief Schleife des Programmes.
 * @attention Funktioniert nur der Rest des Codes abrufbar bzw. vorhanden ist.
 */
void loop()
{
    while (1) {
        while (IFS0bits.T1IF == 0) {
            if (!digitalRead(BUTTON_T0) && !playertwo_turn) {
                playertwo_turns++;
                playertwo_sec += extraTime;
                playertwo_turn = true;
                playerone_turn = false;
                showClock();
                changeLED(false);
            }
            if (!digitalRead(BUTTON_T3) && !playerone_turn) {
                playerone_turns++;
                playerone_sec += extraTime;
                playertwo_turn = false;
                playerone_turn = true;
                showClock();
                changeLED(true);
            }
        }
        // Überprüft ob die Zeit abgelaufen ist
        if (IFS0bits.T1IF == 1) {
            // reset Timer
            IFS0bits.T1IF = 0;
            TMR1 = 0x00;
            PR1 = 62500; // 1 sec

            ClrWdt(); // Reset Watchdog

            if (!digitalRead(INC_SW)) { // öffnet Einstellungen
                openMenu();
                resetGame();
            }
            if (playertwo_turn) {
                playertwo_sec--;
            }
            else if (playerone_turn) {
                playerone_sec--;
            }
            else {
                digitalWriteLEDs(0b0110);
            }

            // Stopt das Spiel wenn keine Zeit, keine Züge mehr übrig sind oder kann manuell geöffnet werden
            if ((playerone_turns >= turns && playertwo_turns >= turns) || playerone_sec == 0 || playertwo_sec == 0 || !digitalRead(BUTTON_T1)) {
                handleEnding();
                resetGame();
            }
        }
        showClock();
    }
}

/** 
 * @brief Hauptklasse sowie Deklaration bzw. Initialisierung der Variablen.
 * @param argc, argv
 * @attention Funktioniert nur wenn der Rest des Codes abrufbar bzw vorhanden ist.
 */
int main(int argc, char** argv)
{

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
    delay_ms(1000);

    loop();

    return (EXIT_SUCCESS);
}