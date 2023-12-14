#include "Init.h"

void setup() {
    matrix.setupMatrix();
    initSound();
    initHighscores();
    initEEPROM();
    display.printIntro();
}

void loop() {
    if(isInGame){
        updateGame();
    }
    else if(millis() > introDuration){
        controller.updateMenu();
        menuUpdate();
        playGameOverSound();
    }
}
