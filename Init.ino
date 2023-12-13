#include "Init.h"

void fullMatrixOn() {
    for(int i = 0; i < matrix.getMatrixSize(); i++) {
        for(int j = 0; j < matrix.getMatrixSize(); j++) {
            matrix.setLed(i, j, true, false);
        }
    }
}

Enemy enemy[1] = {
    Enemy(7, 7)
};

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
    for(int i = 0; i < 1; i++) {
        enemy[i].moveEnemy(7 - i,7 - i);
        enemy[i].setRandomDirection(random(4));
    }
}

void updateGame() {
    player.blink();
    for(int i = 0; i < 1; i++){
        enemy[i].update();
    }
    display.printInGame();
    controller.update();
    gameMap.update();
}