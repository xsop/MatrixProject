#include "GameController.h"

void showUpdatedSettings(){
    if(cursorPos + pagePos == 2){
        fullMatrixOn();
        matrix.setBrightness(currentValue, false);
    }

    if(cursorPos + pagePos == 1){
        display.setBrightness(currentValue, false);
    }
}

Controller::Controller() {
    pinMode(joystickPinX, INPUT);
    pinMode(joystickPinY, INPUT);
    pinMode(joystickPinSwitch, INPUT_PULLUP);
}

void Controller::update() {
    storeJoystickValues();
    if(isNextMoveAvailable(moveDelay)) {
        movePlayer();
    }
    handleButton();
}

void Controller::updateCurrentValue(byte minInput, byte maxInput){
    if(isNextMoveAvailable(adaptiveMenuDelay)){
        if(getDirection() == RIGHT_DIRECTION){
            playScrollSound();
            if(currentValue < maxInput){
                currentValue++;
                changePrint = true;
                adaptiveMenuDelay = max(adaptiveMenuDelay * adaptiveMoveDelayMultiplier, minAdaptiveMoveDelay);
            }
        
        }
        else if(getDirection() == LEFT_DIRECTION){
            playScrollSound();
            if(currentValue > minInput){
                currentValue--;
                changePrint = true;
                adaptiveMenuDelay = max(adaptiveMenuDelay * adaptiveMoveDelayMultiplier, minAdaptiveMoveDelay);
            }
        }
        else{
            adaptiveMenuDelay = menuDelay;
        }
        lastMove = millis();
    }
}

void Controller::updateCurrentChar(char minInput, char maxInput){
    if(isNextMoveAvailable(adaptiveMenuDelay)){
        if(getDirection() == RIGHT_DIRECTION){
            playScrollSound();
            if(currentChar < maxInput){
                currentChar++;
                inputName[cursorPos + pagePos] = currentChar;
                changePrint = true;
                adaptiveMenuDelay = max(adaptiveMenuDelay * adaptiveMoveDelayMultiplier, minAdaptiveMoveDelay);
            }
        }
        else if(getDirection() == LEFT_DIRECTION){
            playScrollSound();
            if(currentChar > minInput){
                currentChar--;
                inputName[cursorPos + pagePos] = currentChar;
                changePrint = true;
                adaptiveMenuDelay = max(adaptiveMenuDelay * adaptiveMoveDelayMultiplier, minAdaptiveMoveDelay);
            }
        }
        else{
            adaptiveMenuDelay = menuDelay;
        }
        lastMove = millis();
    }
}

void Controller::updateMenu() {
    if(isHorizontal){
        display.lcd.setCursor(cursorPos + pagePos, 1);
    }
    else{
        display.lcd.setCursor(0, cursorPos);
    }
    
    display.lcd.blink();
    storeJoystickValues();
    if(isNextMoveAvailable(adaptiveMenuDelay) && menuSwitch != 5) {
        moveMenu(maxPos);
    }
    if(getJoystickButtonRead() != lastJoystickButtonState) {
        if(millis() - lastDebounceTime > debounceDelay) {
            if(getJoystickButtonRead() == LOW) {  
                playButtonSound();
                buttonPressMenuActionHandler();
            }
        }
        lastDebounceTime = millis();
    }

    lastJoystickButtonState = getJoystickButtonRead();
    switch (menuSwitch) {
        case 1:
            updateCurrentValue(0, maxHighscores);
            break;
        case 3:
            updateCurrentValue(0, aboutTextLength - numDisplayRows);
            break;
        case 4:
            updateCurrentValue(0, howToPlayTextLength - numDisplayRows);
            break;
        case 5:
            showUpdatedSettings();
            if(cursorPos + pagePos == 0){
                updateCurrentValue(minNumEnemies, maxNumEnemies);
            }
            else if(cursorPos + pagePos == 1 || cursorPos + pagePos == 2){
                updateCurrentValue(minInput, maxInput);
            }
            break;
        case 8:
            updateCurrentChar('a', 'z');
            break;
    }
}

void Controller::moveMenu(byte maxPos){
    int direction = getDirection();
    switch (direction) {
    case UP_DIRECTION:
        playScrollSound();
        if(cursorPos == 1){
            cursorPos = 0;
            lastMove = millis();
            adaptiveMenuDelay = max(adaptiveMenuDelay * adaptiveMoveDelayMultiplier, minAdaptiveMoveDelay);
        }
        else if(pagePos > 0){
            pagePos --;
            lastMove = millis();
            adaptiveMenuDelay = max(adaptiveMenuDelay * adaptiveMoveDelayMultiplier, minAdaptiveMoveDelay);
            changePrint = true;
        }
        break;

    case DOWN_DIRECTION:
        playScrollSound();
        if(cursorPos == 0){
            cursorPos = 1;
            lastMove = millis();
            adaptiveMenuDelay = max(adaptiveMenuDelay * adaptiveMoveDelayMultiplier, minAdaptiveMoveDelay);
        }
        else if(pagePos < maxPos){
            pagePos++;
            lastMove = millis();
            adaptiveMenuDelay = max(adaptiveMenuDelay * adaptiveMoveDelayMultiplier, minAdaptiveMoveDelay);
            changePrint = true;
        }
        break;
    case LEFT_DIRECTION:
        break;
    case RIGHT_DIRECTION:
        break;
    default:
        adaptiveMenuDelay = menuDelay;
        break;
    }
}

void Controller::storeJoystickValues(){
    joystickValueX = analogRead(joystickPinX);
    joystickValueY = analogRead(joystickPinY);
}

void Controller::handleButton(){
    if(getJoystickButtonRead() != lastJoystickButtonState) {
        if(millis() - lastDebounceTime > debounceDelay) {
            if(getJoystickButtonRead() == LOW) {  
                gameMap.placeBomb();
                playButtonSound();
            }
        }
        lastDebounceTime = millis();
    }

    lastJoystickButtonState = getJoystickButtonRead();
}

int Controller::getDirection() const{
    if (getJoystickValueY() < joystickMinCenterThreshold) {
        return UP_DIRECTION;
    } else if (getJoystickValueY() > joystickMaxCenterThreshold) {
        return DOWN_DIRECTION;
    } else if (getJoystickValueX() < joystickMinCenterThreshold) {
        return LEFT_DIRECTION;
    } else if (getJoystickValueX() > joystickMaxCenterThreshold) {
        return RIGHT_DIRECTION;
    }
    return NO_DIRECTION;
}

void Controller::movePlayer(){
    int direction = getDirection();
    switch(direction) {
        case UP_DIRECTION:
            player.movePlayer(player.getX(), player.getY() - 1);
            lastMove = millis();
            break;
        case DOWN_DIRECTION:
            player.movePlayer(player.getX(), player.getY() + 1);
            lastMove = millis();
            break;
        case LEFT_DIRECTION:
            player.movePlayer(player.getX() - 1, player.getY());
            lastMove = millis();
            break;
        case RIGHT_DIRECTION:
            player.movePlayer(player.getX() + 1, player.getY());
            lastMove = millis();
            break;
        default:
            break;
    }
}

bool Controller::isNextMoveAvailable(int delay) const{
    if(millis() - lastMove > delay) {
        return true;
    }
    return false;
}