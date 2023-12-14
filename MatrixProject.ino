#include "Init.h"

void setup() {
    Serial.begin(115200);

    matrix.setupMatrix();
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
    }

}