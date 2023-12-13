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

Enemy enemy[numEnemies] = {
    Enemy(7, 7),
    Enemy(7, 7)
};

void fullMatrixOn();
void startGame();
void updateGame();