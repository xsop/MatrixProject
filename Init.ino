#include "Init.h"

void endGame() {
    isInGame = false;
    matrix.setupMatrix();
    isInGameOver = true;
    menuSwitch = 6;
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
    // needed to make a new game map
    randomSeed(analogRead(unusedPin));
    gameMap.generate();
    for(int i = 0; i < numEnemies; i++) {
        enemy[i] = Enemy(7 - i,7 - i);
        enemy[i].setRandomDirection(random(4));
    }

    currentScore = 1;

    startGameTime = millis();
}

void enemiesHandler(){
    // Serial.print(enemy[0].getX());
    // Serial.print(" ");
    // Serial.print(enemy[0].getY());
    // Serial.print(" - ");
    // Serial.print(enemy[1].getX());
    // Serial.print(" ");
    // Serial.println(enemy[1].getY());

    if(enemiesKilled == numEnemies){
        endGame();
    }

    if(millis() - blinkTimer >= blinkInterval) {
        blinkTimer = millis();

        for(int i = 0; i < numEnemies; i++) {
            if(enemy[i].isAlive()){
                enemy[i].setVisible(enemyVisible);
            }
            else{
                enemy[i].setVisible(false);
            }
        }
        enemyVisible = !enemyVisible;
    }
    for(int i = 0; i < numEnemies; i++){
        if(enemy[i].isAlive() == false){
            continue;
        }
        if(bomb != nullptr && bomb->getExplosionStart() != 0){
            byte bombX = bomb->getX();
            byte bombY = bomb->getY();
            byte enemyX = enemy[i].getX();
            byte enemyY = enemy[i].getY();
            if((bombX == enemyX && bombY == enemyY)||
            (bombX == enemyX && bombY > enemyY - explosionRadius && bombY < enemyY + explosionRadius)||
            (bombY == enemyY && bombX > enemyX - explosionRadius && bombX < enemyX + explosionRadius)){
                enemy[i].setAlive(false);
                updateScore();
                enemiesKilled++;
                continue;
            }
        }
        if(enemy[i].isOnSameSpot()){
            endGame();
        }
        for(int j = 0; j < numEnemies; j++){
            if(i != j){
                if(enemy[i].getX() == enemy[j].getX() && enemy[i].getY() == enemy[j].getY()){
                    enemy[i].setRandomDirection(random(4));
                }
            }
        }
        enemy[i].pathfind();
    }
}


void updateGame() {
    player.blink();
    enemiesHandler();
    display.printInGame();
    controller.update();
    gameMap.update();
}