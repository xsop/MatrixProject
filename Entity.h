#pragma once

#include "Init.h"

class Entity {
public:
    Entity();
    void blink();
    byte getX() const { return x; }
    byte getY() const { return y; }

protected:
    byte x = playerStartX;
    byte y = playerStartY;

    bool visible = true;
    unsigned long blinkInterval;
    unsigned long lastBlink = 0;
};

class Player : public Entity {
public:
    Player();
    void movePlayer(byte x, byte y);
    bool isOutOfBounds(byte x, byte y) const;
};

class Enemy : public Entity {
public:
    Enemy(byte x, byte y);
    void update();

    void moveEnemy(byte x, byte y);
    bool checkDirection(byte x, byte y);
    void pathfind();

    bool isOutOfBounds(byte x, byte y) const;
    bool isOnSameSpot() const;
    
    long getLastMove() const { return lastMove; }
    void setLastMove(long lastMove) { this->lastMove = lastMove; }

    long getMoveInterval() const { return moveInterval; }
    void setMoveInterval(long moveInterval) { this->moveInterval = moveInterval; }

    byte getRandomDirection() const { return randomDirection; }
    void setRandomDirection(byte randomDirection) { this->randomDirection = randomDirection; }

private:
    byte randomDirection;
    byte randomChanceChangeDirection = 10;

    unsigned long moveInterval = 500;
    unsigned long lastMove = 0;
};

class Bomb : public Entity {
public:
    Bomb();
    Bomb& operator=(const Bomb& other);
    bool timerRanOut() const { return (millis() - timePlaced) > bombTimer; }
    bool exploded();
private:
    unsigned long timePlaced;
    unsigned long explosionStart = 0;    
};

void blinkEntity(unsigned long &lastBlink, unsigned long blinkInterval, bool &visible, byte x, byte y);