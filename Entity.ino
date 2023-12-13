#include "Entity.h"

Entity::Entity() {

}

void Entity::blink() {
    if(areEntitiesOnSameSpot()) {
        // blink faster if player is on top of bomb
        // by having the same blink interval on both
        // the bomb and the player will blink at the same time
        // => not needed to make one entity invisible
        blinkEntity(lastBlink, collisionBlinkInterval, visible, x, y);
    }
    else {
        blinkEntity(lastBlink, blinkInterval, visible, x, y);
    }
}

Player::Player() {
    visible = true;
    blinkInterval = playerBlinkInterval;
}

void Player::movePlayer(byte x, byte y) {
    if(this->x == x && this->y == y) {
        return;
    }
    if(isOutOfBounds(x, y)) {
        return;
    }
    if(gameMap.isObstacle(x, y)) {
        return;
    }
    matrix.setLed(this->x, this->y, matrix.getLed(this->x, this->y), true);

    this->x = x;
    this->y = y;

    matrix.setLed(this->x, this->y, true, false);
    
    lastBlink = millis(); // reset blink timer for consistent first blink
}

bool Player::isOutOfBounds(byte x, byte y) const {
    //needs to be modified to work with a fov type of map
    //this only checks if the player is within the matrix
    int matrixSize = matrix.getMatrixSize() - 1;
    if(x < 0 || x > matrixSize || y < 0 || y > matrixSize) {
        return true;
    }
    return false;
}

Enemy::Enemy() {
    x = 7;
    y = 7;
    visible = true;
    blinkInterval = enemyBlinkInterval;
}

void Enemy::moveEnemy(byte x, byte y) {
    if(this->x == x && this->y == y) {
        return;
    }
    if(isOutOfBounds(x, y)) {
        return;
    }
    if(gameMap.isObstacle(x, y)) {
        return;
    }
    matrix.setLed(this->x, this->y, matrix.getLed(this->x, this->y), true);

    this->x = x;
    this->y = y;

    matrix.setLed(this->x, this->y, true, false);
    
    //lastBlink = millis(); // reset blink timer for consistent first blink
}

void Enemy::pathfinding(){
    if(lastMove + moveInterval < millis()) {
        
        randomChanceChangeDirection = random(100);
        if(randomChanceChangeDirection < 10) {
            randomDirection = random(4);
        }
        switch(randomDirection) {
            case 0:
                if(isOutOfBounds(x, y - 1)){
                    randomDirection = random(4);
                    return;
                }
                if(gameMap.isObstacle(x, y - 1)){
                    randomDirection = random(4);
                    return;
                }
                moveEnemy(x, y - 1);
                break;
            case 1:
                if(isOutOfBounds(x + 1, y)){
                    randomDirection = random(4);
                    return;
                }
                if(gameMap.isObstacle(x + 1, y)){
                    randomDirection = random(4);
                    return;
                }
                moveEnemy(x + 1, y);
                break;
            case 2:
                if(isOutOfBounds(x, y + 1)){
                    randomDirection = random(4);
                    return;
                }
                if(gameMap.isObstacle(x, y + 1)){
                    randomDirection = random(4);
                    return;
                }
                moveEnemy(x, y + 1);
                break;
            case 3:
                if(isOutOfBounds(x - 1, y)){
                    randomDirection = random(4);
                    return;
                }
                if(gameMap.isObstacle(x - 1, y)){
                    randomDirection = random(4);
                    return;
                }
                moveEnemy(x - 1, y);
                break;
        }
        lastMove = millis();
    }
}

bool Enemy::isOutOfBounds(byte x, byte y) const {
    //needs to be modified to work with a fov type of map
    //this only checks if the player is within the matrix
    int matrixSize = matrix.getMatrixSize() - 1;
    if(x < 0 || x > matrixSize || y < 0 || y > matrixSize) {
        return true;
    }
    return false;
}

bool Enemy::isOnSameSpot() const {
    if(player.getX() == x && player.getY() == y) {
        isInGame = false;
        matrix.setupMatrix();
        isInGameOver = true;
        display.printGameOver();
        return true;
    }
    return false;
}

Bomb::Bomb() {
    visible = true;
    blinkInterval = bombBlinkInterval;
    timePlaced = millis();
    x = player.getX();
    y = player.getY();
}

Bomb& Bomb::operator=(const Bomb& other) {
    x = other.x;
    y = other.y;
    visible = other.visible;
    blinkInterval = other.blinkInterval;
    lastBlink = other.lastBlink;
    return *this;
}

bool Bomb::exploded() {
    if(explosionStart == 0){
        for(int i = 0; i < explosionRadius; i++) {
            matrix.setLed(x + i, y, true, false);
            matrix.setLed(x - i, y, true, false);
            matrix.setLed(x, y + i, true, false);
            matrix.setLed(x, y - i, true, false);
            explosionStart = millis();
        }
        // if player is on the same row and within the explosion radius
        if((player.getX() <= x + (explosionRadius - 1) && 
            player.getX() >= x - (explosionRadius - 1) && 
            player.getY() == y) ||
        // if player is on the same column and within the explosion radius
            (player.getY() <= y + (explosionRadius - 1) &&
             player.getY() >= y - (explosionRadius - 1) && 
             player.getX() == x)) {

            // startGame();
            isInGame = false;
            matrix.setupMatrix();
            isInGameOver = true;
            display.printGameOver();
            
        }

    }
    else if(millis() - explosionStart > animationDuration) {
        for(int i = 0; i < explosionRadius; i++) {
            matrix.setLed(x + i, y, matrix.getLed(x + i, y), true);
            matrix.setLed(x - i, y, matrix.getLed(x - i, y), true);
            matrix.setLed(x, y + i, matrix.getLed(x, y + i), true);
            matrix.setLed(x, y - i, matrix.getLed(x, y - i), true);
        }
        explosionStart = 0;
        return 1;
    }
    return 0;
}

void blinkEntity(unsigned long &lastBlink, unsigned long blinkInterval, bool &visible, byte x, byte y) {
    if(millis() - lastBlink > blinkInterval) {
        lastBlink = millis();
        
        matrix.setLed(x, y, visible, false);
        visible = !visible;
    }
}