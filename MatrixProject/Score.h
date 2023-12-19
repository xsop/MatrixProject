#pragma once

#include "Init.h"

unsigned long startGameTime = 0;
char inputName[3];

int currentScore = 0;
int highscores[3] = {0, 0, 0};
char highscoresName[3][4] = {"NAN", "NAN", "NAN"};

void initHighscores();
byte getHighscorePos();
void saveHighscores();
void resetHighscores();
void updateScore();