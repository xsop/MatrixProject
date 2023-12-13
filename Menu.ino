#include "Menu.h"

void menu(){

    byte index = cursorPos + pagePos;
    if(menuSwitch == 0){
        if(index == 0){
            startGame();
            isInGame = true;
        }
        else if(index == 1){ //highscores
            changePrint = true;
            menuSwitch = 1;
            cursorPos = 0;
            pagePos = 0;
            maxPos = 0;
        }
        else if(index == 2){ //settings
            changePrint = true;
            menuSwitch = 2;
            cursorPos = 0;
            pagePos = 0;
            maxPos = 3;
        }
        else if(index == 3){ //about
            changePrint = true;
            menuSwitch = 3;
            cursorPos = 0;
            pagePos = 0;
        }
    }
    else if(menuSwitch == 1){
        if(index == 1){
            changePrint = true;
            menuSwitch = 0;
            maxPos = 3;
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
        else if(index == 2){
            changePrint = true;
            soundEnabled = !soundEnabled;
        }
        else if(index == 4){
            changePrint = true;
            menuSwitch = 0;
            maxPos = 3;
            cursorPos = 0;
            pagePos = 0;
        }
    }
    else if(menuSwitch == 3){
        changePrint = true;
        menuSwitch = 0;
        maxPos = 3;
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
        else if(menuSwitch == 1){
            display.printHighscores();
        }
        else if(menuSwitch == 2){
            display.printSettings();
        }
        else if(menuSwitch == 3){
            display.printAbout();
        }
        else if(menuSwitch == 5){
            display.printValueInput();
        }

        changePrint = false;
    }
}