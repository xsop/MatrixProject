#pragma once

#include "EEPROM.h"
#include "Consts.h"
#include "Variables.h"
#include "MatrixLed.h"
#include "Entity.h"
#include "GameController.h"
#include "Map.h"
#include "LCD.h"
#include "Menu.h"
#include "Score.h"
#include "Sound.h"

Matrix matrix;
Player player;

Controller controller;
GameMap gameMap;
Display display;

void endGame();
void fullMatrixOn();
void startGame();
void initEEPROM();
bool isPlayerOnBomb();

void updateGame();