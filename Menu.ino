#include "Menu.h"

void menu(){
    byte index = cursorPos + pagePos;
    if(isInMain){
        if(index == 0){
            startGame();
            isInGame = true;
        }
        if(index == 2){
            changePrint = true;
            isInMain = false;
            isInSettings = true;
            isInAbout = false;
            isInValueInput = false;
            cursorPos = 0;
            pagePos = 0;
        }
        else if(index == 3){
            changePrint = true;
            isInMain = false;
            isInSettings = false;
            isInAbout = true;
            isInValueInput = false;
            cursorPos = 0;
            pagePos = 0;
        }
    }
    else if(isInSettings){
        if(index == 0 || index == 1){
            if(index == 0){
                currentValue = display.getBrightness();
            }
            else if(index == 1){
                currentValue = matrix.getBrightness();
            }
            changePrint = true;
            isInMain = false;
            isInSettings = false;
            isInAbout = false;
            isInValueInput = true;
        }
        else if(index == 4){
            changePrint = true;
            isInMain = true;
            isInSettings = false;
            isInAbout = false;
            isInValueInput = false;
            cursorPos = 0;
            pagePos = 0;
        }
    }
    else if(isInAbout){
        changePrint = true;
        isInMain = true;
        isInSettings = false;
        isInAbout = false;
        isInValueInput = false;
        cursorPos = 0;
        pagePos = 0;
    }
    else if(isInValueInput){
        changePrint = true;
        isInMain = false;
        isInSettings = true;
        isInAbout = false;
        isInValueInput = false;
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

        if(isInMain){
            display.printMainMenu();
        }
        if(isInSettings){
            display.printSettings();
        }
        if(isInAbout){
            display.printAbout();
        }
        if(isInValueInput){
            display.printValueInput();
        }

        changePrint = false;
    }
}