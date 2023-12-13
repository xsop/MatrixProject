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

void fullMatrixOn();
void startGame();
void updateGame();