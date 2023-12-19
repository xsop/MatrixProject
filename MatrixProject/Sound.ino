#include "Sound.h"

void initSound(){
    pinMode(buzzerPin, OUTPUT);
}

bool playMelody(int thisNote, int melody[]){
    if(!soundEnabled)
        return;
    if(millis() - lastNoteTime >= noteDuration){
        noTone(buzzerPin);
        divider = melody[thisNote + 1];
        if (divider > 0) {
            noteDuration = (wholenote) / divider;
        } 
        else if (divider < 0) {
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5;
        }
        tone(buzzerPin, melody[thisNote], noteDuration*0.9);
        lastNoteTime = millis();
        return 1;
    }
    return 0;
}

void playMainTheme(){
    if(!soundEnabled)
        return;
    if(playMelody(thisNote, inGameSoundTrack)){
        if(thisNote < inGameSoundTrackNotes * 2){
            thisNote = thisNote + 2;
        }
        else{
            thisNote = 0;
        }
    }
}

void playGameOverSound(){
    if(!soundEnabled)
        timesToPlayGameOver = 0;
        return;
    if(!timesToPlayGameOver){
        return;
    }
    if(playMelody(thisNoteGameOver, gameOverSound)){
        if(thisNoteGameOver < gameOverSoundNotes * 2){
            thisNoteGameOver = thisNoteGameOver + 2;
        }
        else{
            timesToPlayGameOver --;
            noTone(buzzerPin);
            thisNoteGameOver = 0;
        }
    }
}

void playButtonSound(){
    if(!soundEnabled)
        return;
    tone(buzzerPin, NOTE_C4, 100);
}

void playScrollSound(){
    if(!soundEnabled)
        return;
    tone(buzzerPin, NOTE_C7, 50);
}

void playEnemyDeathSound(){
    if(!soundEnabled)
        return;
    tone(buzzerPin, NOTE_D8, 100);
}