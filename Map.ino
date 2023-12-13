#include "Init.h"

GameMap::GameMap() {
    setMatrixSize(matrix.getMatrixSize());
}

void GameMap::update() {
    if(bomb != nullptr) {
        if(bomb->timerRanOut()) {
            if(bomb->exploded()){
                delete bomb;
                bomb = nullptr;
                return;
            }
        }
        bomb->blink();
    }
}

void GameMap::generate() {
    int wallCount = (matrixSize * matrixSize) * wallPercentage / 100;
    if(wallCount < 1) {
        wallCount = 1;
    }
    byte wallX = 0;
    byte wallY = 0;

    for(int i = 0; i < matrixSize; i+=2) {
        for(int j = 0; j < matrixSize; j+=2) {
            matrix.setLed(i, j, true);
        }
    }
}

void GameMap::placeBomb() {
    if(bomb != nullptr) {
        return;
    }
    bomb = new Bomb();
}

bool GameMap::isObstacle(int x, int y) const {
    // not necessary to have a specific function for this
    // but makes it more modular and easier to modify later
    return matrix.getLed(x, y);
}

bool areEntitiesOnSameSpot(){
    if (bomb == nullptr) {
        return false;
    }
    if (player.getX() == bomb->getX() && player.getY() == bomb->getY()) {
        return true;
    }
    return false;
}