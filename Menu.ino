#include "Menu.h"

void menu(){
    byte index = cursorPos + pagePos;
    if(menuSwitch == 0){
        if(index == 0){
            startGame();
            isInGame = true;
        }
        if(index == 2){ //settings
            changePrint = true;
            menuSwitch = 2;
            cursorPos = 0;
            pagePos = 0;
        }
        else if(index == 3){ //about
            changePrint = true;
            menuSwitch = 3;
            cursorPos = 0;
            pagePos = 0;
        }
    }
    else if(menuSwitch == 2){
        if(index == 0 || index == 1){
            if(index == 0){
                currentValue = display.getBrightness();
            }
            else if(index == 1){
                currentValue = matrix.getBrightness();
            }
            changePrint = true;
            menuSwitch = 5;
        }
        else if(index == 4){
            changePrint = true;
            menuSwitch = 0;
            cursorPos = 0;
            pagePos = 0;
        }
    }
    else if(menuSwitch == 3){
        changePrint = true;
        menuSwitch = 0;
        cursorPos = 0;
        pagePos = 0;
    }
    else if(menuSwitch == 5){
        changePrint = true;
        menuSwitch = 2;
        if(index == 0){
            display.setBrightness(currentValue);
        }
        else if(index == 1){
            matrix.setBrightness(currentValue);
        }
        cursorPos = 0;
        pagePos = 0;
    }
}

void menuUpdate(){
    if(changePrint){

        if(menuSwitch == 0){
            display.printMainMenu();
        }
        if(menuSwitch == 2){
            display.printSettings();
        }
        if(menuSwitch == 3){
            display.printAbout();
        }
        if(menuSwitch == 5){
            display.printValueInput();
        }

        changePrint = false;
    }
    Serial.println(menuSwitch);
}