#pragma once

#include "Init.h"
#include "Consts.h"
#include "LiquidCrystal.h"

class Display {
public:
    Display();
    void printIntro();
    void printMainMenu();
    void printHighscores();
    void printSettings();
    void printAbout();
    void printHowToPlay();
    void printValueInput();
    void printNameInput();
    void printGameOver();
    void printNewScore();
    void printInGame();

    void setBrightness(int brightness);
    int getBrightness();

    LiquidCrystal lcd = LiquidCrystal(rs, en, d4, d5, d6, d7);
};

char* aboutText = "by Stefan Paun: github.com/xsop";
const byte aboutTextLength = strlen(aboutText);

char* howToPlay = "Place bombs by pressing the button, move with the joystick, kill enemies fast for a highscore.";
const byte howToPlayTextLength = strlen(howToPlay);