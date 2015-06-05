#include "buzzer.h"
#include <Arduino.h>

Buzzer::Buzzer() {
  pinMode(BUZZER_PIN, OUTPUT);
  tempo = 300;  
}

void Buzzer::playNote(char note, int beat) {
 
  int freq = getFrequency(note);
  if (freq == -1) {
    // not supported
    return;
  }
  else if (freq == 0) {
    // rest
    delay(beat * tempo); 
  }
  else {
    playTone(freq, beat * tempo);
  }
}

void Buzzer::playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(BUZZER_PIN, HIGH);
    delayMicroseconds(tone);
    digitalWrite(BUZZER_PIN, LOW);
    delayMicroseconds(tone);
  }
  // pause between notes
  delay(tempo / 2); 
}

int Buzzer::getFrequency(char note) {
  switch (note) {
    case 'c':
      return 1915;
    case 'd':
      return 1700;
    case 'e':
      return 1519;
    case 'f':
      return 1432;
    case 'g':
      return 1275;
    case 'a':
      return 1136;
    case 'b':
      return 1014;
    case 'C':
      return 956;
    case '-':
      return 0;
    default:
      return -1;
  }
  
}

  
