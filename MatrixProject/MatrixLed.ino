#include "MatrixLed.h"

Matrix::Matrix(){

}

void Matrix::setupMatrix(){
    // the zero refers to the MAX7219 number, it is zero for 1 chip
    lc.shutdown(0, false); // turn off power saving, enables display
    lc.setIntensity(0, matrixBrightness); // sets brightness (0~15 possible values)
    lc.clearDisplay(0);// clear screen
    resetMemory();
}

void Matrix::resetMemory(){
    for(int i = 0; i < matrixSize; i++){
        for(int j = 0; j < matrixSize; j++){
            memoryMatrix[i][j] = 0;
        }
    }
    memoryCounter = 0;
}

void Matrix::setLed(byte row, byte col, bool state, bool updateMatrix = 1){
    if(row < 0 || row > matrixSize - 1 || col < 0 || col > matrixSize - 1) {
        return;
    }
    lc.setLed(0, row, col, state);
    if(updateMatrix && memoryMatrix[row][col] != state){
        memoryMatrix[row][col] = state;
        memoryCounter += state ? 1 : -1;
    }
}


bool Matrix::getLed(byte row, byte col) const {
    return memoryMatrix[row][col];
}

void Matrix::setBrightness(int brightness, bool setEEPROM){
    if(brightness < minInput ){
        brightness = minInput;
    }
    else if(brightness > maxInput){
        brightness = maxInput;
    }
    matrixBrightness = map(brightness, minInput, maxInput, 0, 15);
    lc.setIntensity(0, matrixBrightness);
    if(setEEPROM){
        EEPROM.update(matrixBrightnessAddress, matrixBrightness);
    }
}

int Matrix::getBrightness(){
    return matrixBrightness;
}