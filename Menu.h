#pragma once

#include "Init.h"

bool isInGame = false;
byte cursorPos = 0;
byte pagePos = 0;
bool changePrint = true;

byte menuSwitch = 0;
byte maxPos = 3;
byte currentValue = 0;
char currentChar = 'a';
bool isInGameOver = false;
bool isInNewScore = false;
bool isInInputName = false;

void menu();
void menuUpdate();