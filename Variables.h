#pragma once

#include "Consts.h"
#include "Entity.h"

int adaptiveMoveDelay = moveDelay;
int adaptiveMenuDelay = menuDelay;

int matrixBrightness = 2;
int LCDBrightness = 255;

bool soundEnabled = true;
bool isHorizontal = false;

bool enemiesVisible = false; //all enemies blinker
unsigned long blinkTimer = 0;
unsigned long blinkInterval = 150; 

byte enemiesKilled = 0;

Enemy enemy[numEnemies] = {
    Enemy(7, 7),
    Enemy(7, 7)
};