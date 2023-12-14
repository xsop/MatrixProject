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

void setMenu(struct MenuStruct menuStruct); // Added 'struct' before MenuStruct
void menu();
void menuUpdate();