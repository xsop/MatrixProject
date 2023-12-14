#include "Score.h"

void initHighscores(){
    inputName[0] = 'a';
    inputName[1] = 'a';
    inputName[2] = 'a';

    for(int i = 0; i < 3; i++){
        if(EEPROM.read(highscoresNameAddress[i]) >= 'a' && EEPROM.read(highscoresNameAddress[i]) <= 'z'){
            EEPROM.get(highscoresAddress[i], highscores[i]);
            EEPROM.get(highscoresNameAddress[i], highscoresName[i]);
        }

        // Serial.print(highscoresName[i]);
        // Serial.print(" - ");
        // Serial.println(highscores[i]);
        for(int j = 0; j < 3; j++){
            Serial.print(highscoresName[i][j]);
        }
        Serial.print(" - ");
        Serial.print(highscores[i]);
        Serial.println();
    }
}

byte getHighscorePos(){
    for(int i = 0; i < 3; i++){
        if(currentScore > highscores[i]){
            return i;
        }
    }
    return 3;
}

void saveHighscores(){
    byte pos = getHighscorePos();
    if(pos == 3){
        return;
    }
    for(int i = 2; i > pos; i--){
        EEPROM.put(highscoresAddress[i], highscores[i - 1]);
        EEPROM.put(highscoresNameAddress[i], highscoresName[i - 1]);
        highscores[i] = highscores[i - 1];
        for(int j = 0; j < 3; j++){
            highscoresName[i][j] = highscoresName[i - 1][j];
        }
    }
    EEPROM.put(highscoresAddress[pos], currentScore);
    EEPROM.put(highscoresNameAddress[pos], inputName);    
    highscores[pos] = currentScore;
    for(int j = 0; j < 3; j++){
        highscoresName[pos][j] = inputName[j];
    }
}

void resetHighscores(){
    for(int i = 0; i < 3; i++){
        EEPROM.put(highscoresAddress[i], 0);
        EEPROM.put(highscoresNameAddress[i], "NAN");
        highscores[i] = 0;
        highscoresName[i][0] = 'N';
        highscoresName[i][1] = 'A';
        highscoresName[i][2] = 'N';
    }
}

void updateScore(){
    currentScore += maxScorePerEnemy - min(maxScorePerEnemy, map((millis() - startGameTime), 0, 120000, 0, maxScorePerEnemy));
}