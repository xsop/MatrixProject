#include "Init.h"

void setup() {
    Serial.begin(115200);

    matrix.setupMatrix();

    matrixBrightness = EEPROM.read(matrixBrightnessAddress);
    if(matrixBrightness > 15 || matrixBrightness < 0){
        matrixBrightness = 15;
    }
    matrix.setBrightness(matrixBrightness);

    LCDBrightness = EEPROM.read(LCDBrightnessAddress);
    if(LCDBrightness > 255 || LCDBrightness < 0){
        LCDBrightness = 255;
    }
    display.setBrightness(map(LCDBrightness, 0, 255, minInput, maxInput));

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