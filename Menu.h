#pragma once

#include "Init.h"

bool isInGame = false;
byte cursorPos = 0;
byte pagePos = 0;
bool changePrint = true;
// bool isInMain = true;
// bool isInHighScores = false;
// bool isInSettings = false;
// bool isInAbout = false;
// bool isInValueInput = false;

byte menuSwitch = 0;
byte maxPos = 3;
byte currentValue = 0;
bool isInGameOver = false;

void menu();
void menuUpdate();