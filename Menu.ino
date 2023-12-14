#include "Menu.h"

void menu(){

    byte index = cursorPos + pagePos;
    if(menuSwitch == 0){ //main
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
            currentValue = 0;
        }
        else if(index == 2){ //settings
            changePrint = true;
            menuSwitch = 2;
            cursorPos = 0;
            pagePos = 0;
            maxPos = 3;
            currentValue = 0;
        }
        else if(index == 3){ //about
            changePrint = true;
            menuSwitch = 3;
            cursorPos = 0;
            pagePos = 0;
            currentValue = 0;
        }
        else if(index == 4){ //how to play
            changePrint = true;
            menuSwitch = 4;
            maxPos = 0;
            cursorPos = 0;
            pagePos = 0;
            currentValue = 0;
        }
    }
    else if(menuSwitch == 1){ //highscores
        if(index == 1){
            changePrint = true;
            menuSwitch = 0;
            maxPos = 3;
            cursorPos = 0;
            pagePos = 0;
            currentValue = 0;
        }
        
    }
    else if(menuSwitch == 2){ //settings
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
            EEPROM.update(soundEnabledAddress, soundEnabled);
        }
        else if(index == 3){
            resetHighscores();
            changePrint = true;
            menuSwitch = 2;
            cursorPos = 0;
            pagePos = 0;
            currentValue = 0;
        }
        else if(index == 4){
            changePrint = true;
            menuSwitch = 0;
            maxPos = 3;
            cursorPos = 0;
            pagePos = 0;
            currentValue = 0;
        }
    }
    else if(menuSwitch == 3){ //about
        changePrint = true;
        menuSwitch = 0;
        maxPos = 3;
        cursorPos = 0;
        pagePos = 0;
        currentValue = 0;
    }
    else if(menuSwitch == 4){ //how to play
        if(index == 1){
            changePrint = true;
            menuSwitch = 0;
            maxPos = 3;
            cursorPos = 0;
            pagePos = 0;
            currentValue = 0;
        }
    }
    else if(menuSwitch == 5){ //value input
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
        currentValue = 0;
    }
    else if(menuSwitch == 6){ //game over
        changePrint = true;
        if(getHighscorePos() < 3){
            Serial.println(getHighscorePos());
            menuSwitch = 7;
            cursorPos = 0;
            pagePos = 0;
            currentValue = 0;
        }
        else{
            menuSwitch = 0;
            cursorPos = 0;
            pagePos = 0;
            currentValue = 0;
            maxPos = 3;
        }
        
    }
    else if(menuSwitch == 7){ //show highscore
        changePrint = true;
        menuSwitch = 8;
        cursorPos = 0;
        pagePos = 0;
        maxPos = 1;
        currentValue = 0;
        isHorizontal = true;
    }
    else if(menuSwitch == 8){ //input name
        saveHighscores();
        changePrint = true;
        menuSwitch = 0;
        cursorPos = 0;
        pagePos = 0;
        inputName[0] = 'a';
        inputName[1] = 'a';
        inputName[2] = 'a';
        maxPos = 3;
        currentValue = 0;
        isHorizontal = false;
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
        else if(menuSwitch == 4){
            display.printHowToPlay();
        }
        else if(menuSwitch == 5){
            display.printValueInput();
        }
        else if(menuSwitch == 6){
            display.printGameOver();
        }
        else if(menuSwitch == 7){
            display.printNewScore();
        }
        else if(menuSwitch == 8){
            display.printNameInput();
        }

        changePrint = false;
    }
}