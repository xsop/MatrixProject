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