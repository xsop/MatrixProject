#include "LCD.h"

Display::Display() {
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    analogWrite(displayLedPin, LCDBrightness);
}

void Display::printIntro() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Welcome to");
    lcd.setCursor(0, 1);
    lcd.print("BOMBERMAN");
}

char* mainMenuTitles[5] = {"Play", "Highscores", "Settings", "About", "How to play"};

void Display::printMainMenu() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(mainMenuTitles[pagePos]);
    lcd.setCursor(0, 1);
    lcd.print(mainMenuTitles[pagePos + 1]);
}

void Display::printHighscores() {
    lcd.clear();
    lcd.setCursor(0, 0);
    // lcd.print(highscoresName[currentValue]);
    for(int i = 0; i < 3; i++){
        lcd.print(highscoresName[currentValue][i]);
    }
    lcd.print(" - ");
    lcd.print(highscores[currentValue]);
    lcd.setCursor(0, 1);
    lcd.print("Back");
}

char* settingsTitles[5] = {"LCD Brightness", "Matrix Brightness", "Sound: ", "Reset highscores", "Back"};

void Display::printSettings() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(settingsTitles[pagePos]);
    if(pagePos == 2){
        lcd.print(soundEnabled ? "On" : "Off");
    }
    lcd.setCursor(0, 1);
    lcd.print(settingsTitles[pagePos + 1]);
    if(pagePos + 1 == 2){
        lcd.print(soundEnabled ? "On" : "Off");
    }
}

void Display::printAbout(){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("BOMBERMAN");
    lcd.setCursor(0, 1);
    for(int i = 0; i < 16; i++){
        lcd.print(aboutText[i + currentValue]);
    }
}

void Display::printHowToPlay(){
    lcd.clear();
    lcd.setCursor(0, 0);
    for(int i = 0; i < 16; i++){
        lcd.print(howToPlay[i + currentValue]);
    }
    lcd.setCursor(0, 1);
    lcd.print("Back");
}

void Display::printValueInput(){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter value:");
    lcd.setCursor(0, 1);
    lcd.print(currentValue);
}

void Display::printNameInput(){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter name:");
    lcd.setCursor(0, 1);
    for(int i = 0; i < 3; i++){
        if(inputName[i] >= 'a' && inputName[i] <= 'z'){
            lcd.print(inputName[i]);
        }
        else{
            lcd.print("_");
        }
    }
}

void Display::printGameOver(){
    lcd.setCursor(0, 0);
    lcd.print("GAME OVER         ");
}

void Display::printNewScore(){
    lcd.setCursor(0, 0);
    lcd.print("Highscore!      ");
    lcd.setCursor(0, 1);
    lcd.print("Score: ");
    lcd.print(currentScore);
    lcd.print("      ");
}

void Display::printInGame(){
    lcd.setCursor(0, 0);
    lcd.print("Enemies left: ");
    lcd.print(numEnemies - enemiesKilled);
    lcd.setCursor(0, 1);
    lcd.print("           ");
}

void Display::setBrightness(int brightness){
    if(brightness < minInput){
        brightness = minInput;
    }
    else if(brightness > maxInput){
        brightness = maxInput;
    }
    LCDBrightness = map(brightness, minInput, maxInput, 0, 255);
    analogWrite(displayLedPin, LCDBrightness);
    EEPROM.update(LCDBrightnessAddress, LCDBrightness);
}

int Display::getBrightness(){
    return map(LCDBrightness, 0, 255, minInput, maxInput);
}