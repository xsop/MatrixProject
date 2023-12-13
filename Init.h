#pragma once

#include "EEPROM.h"
#include "Consts.h"
#include "MatrixLed.h"
#include "Entity.h"
#include "GameController.h"
#include "Map.h"
#include "LCD.h"
#include "Menu.h"

Matrix matrix;
Player player;

Controller controller;
GameMap gameMap;
Display display;

bool enemyVisible = false;
unsigned long blinkTimer = 0;
unsigned long blinkInterval = 150; 

const byte numEnemies = 2;
byte enemiesKilled = 0;

Enemy enemy[numEnemies] = {
    Enemy(7, 7),
    Enemy(7, 7)
};

bool soundEnabled = true;

char* aboutText = "by Stefan Paun: github.com/xsop";
byte aboutTextLength = 32;

int currentScore = 0;
unsigned long startGameTime = 0;

void endGame();
void fullMatrixOn();
void startGame();
void updateGame();