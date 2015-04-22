#ifndef BUZZER_H
#define BUZZER_H

#define BUZZER_PIN 8

class Buzzer {
  
  public:
    Buzzer();
    void playNote(char note, int beat);
    
  private:
    int tempo;
    void playTone(int tone, int duration);
    int getFrequency(char note);
  
};

#endif
