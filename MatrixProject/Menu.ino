#include "Menu.h"

struct MenuStruct {
    bool changePrint;
    byte menuSwitch;
    byte cursorPos;
    byte pagePos;
    byte maxPos;
    byte currentValue;
};

void setMenu(struct MenuStruct menuStruct){
    changePrint = menuStruct.changePrint;
    menuSwitch = menuStruct.menuSwitch;
    cursorPos = menuStruct.cursorPos;
    pagePos = menuStruct.pagePos;
    maxPos = menuStruct.maxPos;
    currentValue = menuStruct.currentValue;
}

MenuStruct menuStruct[] = {
    {true, 0, 0, 0, 3, 0}, //main
    {true, 1, 0, 0, 0, 0}, //highscores
    {true, 2, 0, 0, 4, 0}, //settings
    {true, 3, 0, 0, 0, 0}, //about
    {true, 4, 0, 0, 0, 0}, //how to play
    {true, 5, 0, 0, 0, 0}, //value input
    {true, 6, 0, 0, 0, 0}, //game over
    {true, 7, 0, 0, 0, 0}, //show highscore
    {true, 8, 0, 0, 1, 0} //input name
};

void buttonPressMenuActionHandler(){
    byte index = cursorPos + pagePos;
    if(menuSwitch == 0){ //main
        if(index == 0){
            startGame();
            isInGame = true;
        }
        else if(index == 1){ //highscores
            setMenu(menuStruct[index]);
        }
        else if(index == 2){ //settings
            setMenu(menuStruct[index]);
        }
        else if(index == 3){ //about
            setMenu(menuStruct[index]);
        }
        else if(index == 4){ //how to play
            setMenu(menuStruct[index]);
        }
    }
    else if(menuSwitch == 1){ //highscores
        if(index == 1){
            setMenu(menuStruct[0]);
        }
        
    }
    else if(menuSwitch == 2){ //settings
        if(index == 0 || index == 1 || index == 2){
            if(index == 0){
                currentValue = numEnemies;
            }
            else if(index == 1){
                currentValue = display.getBrightness();
            }
            else if(index == 2){
                currentValue = matrix.getBrightness();
            }
            changePrint = true;
            menuSwitch = 5;
        }
        else if(index == 3){
            changePrint = true;
            soundEnabled = !soundEnabled;
            EEPROM.update(soundEnabledAddress, soundEnabled);
        }
        else if(index == 4){
            resetHighscores();
            setMenu(menuStruct[2]);
        }
        else if(index == 5){
            setMenu(menuStruct[0]);
        }
    }
    else if(menuSwitch == 3){ //about
        setMenu(menuStruct[0]);
    }
    else if(menuSwitch == 4){ //how to play
        if(index == 1){
            setMenu(menuStruct[0]);
        }
    }
    else if(menuSwitch == 5){ //value input
        changePrint = true;
        menuSwitch = 2;
        cursorPos = 0;
        pagePos = 0;
        if(index == 0){
            numEnemies = currentValue;
            EEPROM.update(numEnemiesAddress, numEnemies);
        }
        else if(index == 1){
            display.setBrightness(currentValue, true);
        }
        else if(index == 2){
            matrix.setupMatrix();
            matrix.setBrightness(currentValue, true);
        }
        currentValue = 0;
    }
    else if(menuSwitch == 6){ //game over
        if(getHighscorePos() < 3){
            setMenu(menuStruct[7]);
        }
        else{
            setMenu(menuStruct[0]);
        }
        
    }
    else if(menuSwitch == 7){ //show highscore
        setMenu(menuStruct[8]);
        isHorizontal = true;
    }
    else if(menuSwitch == 8){ //input name
        saveHighscores();
        setMenu(menuStruct[0]);
        inputName[0] = 'a';
        inputName[1] = 'a';
        inputName[2] = 'a';

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