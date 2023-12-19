#include "Init.h"

void endGame() {
    timesToPlayGameOver = 1;
    isInGame = false;
    matrix.setupMatrix();
    menuSwitch = 6;
    changePrint = true;
    display.printGameOver();
    enemiesKilled = 0;
}

void fullMatrixOn() {
    for(int i = 0; i < matrix.getMatrixSize(); i++) {
        for(int j = 0; j < matrix.getMatrixSize(); j++) {
            matrix.setLed(i, j, true, false);
        }
    }
}

void startGame() {
    //make the whole matrix red with delay
    fullMatrixOn();
    delay(fullMatrixOnDelay);
    
    //putting everything back to the initial state
    player.movePlayer(playerStartX, playerStartY);

    matrix.setupMatrix();
    // regenerate random seed
    randomSeed(analogRead(unusedPin));
    gameMap.generate();
    for(int i = 0; i < numEnemies; i++) {
        enemy[i] = Enemy(enemyStartX, enemyStartY);
        enemy[i].setRandomDirection(random(4));
    }

    currentScore = 0;
    startGameTime = millis();
}

void enemiesHandler(){
    if(enemiesKilled == numEnemies){
        endGame();
    }
    // blink all enemies at roughly the same time
    // depending on the entity blinkInterval seems
    // to have a delay between them since initialisation
    // is taking some time
    if(millis() - blinkTimer >= blinkInterval) {
        blinkTimer = millis();

        for(int i = 0; i < numEnemies; i++) {
            if(enemy[i].isAlive()){
                enemy[i].setVisible(enemiesVisible);
            }
            else if(!enemy[i].isOnSameSpotAsPlayer()){
                enemy[i].setVisible(false);
            }
        }
    
        enemiesVisible = !enemiesVisible;
    }
    // process enemies
    for(int i = 0; i < numEnemies; i++){
        // skip dead enemies
        if(enemy[i].isAlive() == false){
            continue;
        }
        // check if enemy is on the same spot as the bomb explosionRadius
        if(bomb != nullptr && bomb->getExplosionStart() != 0){
            byte bombX = bomb->getX();
            byte bombY = bomb->getY();
            byte enemyX = enemy[i].getX();
            byte enemyY = enemy[i].getY();

            // bomb killed enemy
            if((bombX == enemyX && bombY == enemyY)||
            (bombX == enemyX && bombY > enemyY - explosionRadius && bombY < enemyY + explosionRadius)||
            (bombY == enemyY && bombX > enemyX - explosionRadius && bombX < enemyX + explosionRadius)){
                enemy[i].setAlive(false);
                playEnemyDeathSound();
                updateScore();
                enemiesKilled++;
                continue;
            }
        }

        // enemy killed player
        if(enemy[i].isOnSameSpotAsPlayer()){
            endGame();
        }

        // enemies on the same spot -> choose a random direction
        // still a small chance that they will remain on the same spot
        // and direction will be chosen again
        for(int j = 0; j < numEnemies; j++){
            if(i != j){
                if(enemy[i].getX() == enemy[j].getX() && enemy[i].getY() == enemy[j].getY()){
                    enemy[i].setRandomDirection(random(4));
                }
            }
        }
        // move enemy
        enemy[i].pathfind();
    }
}

void initEEPROM() {
    soundEnabled = EEPROM.read(soundEnabledAddress) & 0x01;

    numEnemies = EEPROM.read(numEnemiesAddress);
    if(numEnemies > maxNumEnemies || numEnemies < minNumEnemies){
        numEnemies = maxNumEnemies;
    }
        
    matrixBrightness = EEPROM.read(matrixBrightnessAddress);
    if(matrixBrightness > maxMatrixBrightness || matrixBrightness < minMatrixBrightness){
        matrixBrightness = maxMatrixBrightness;
    }
    matrix.setBrightness(map(matrixBrightness, minMatrixBrightness, maxMatrixBrightness, minInput, maxInput), true);

    LCDBrightness = EEPROM.read(LCDBrightnessAddress);
    if(LCDBrightness > maxLCDBrightness || LCDBrightness < minLCDBrightness){
        LCDBrightness = maxLCDBrightness;
    }
    display.setBrightness(map(LCDBrightness, minLCDBrightness, maxLCDBrightness, minInput, maxInput), true);
}

bool isPlayerOnBomb(){
    if (bomb == nullptr) {
        return false;
    }
    if (player.getX() == bomb->getX() && player.getY() == bomb->getY()) {
        return true;
    }
    return false;
}

void updateGame() {
    player.blink();
    enemiesHandler();
    display.printInGame();
    controller.update();
    gameMap.update();
    playMainTheme();
}