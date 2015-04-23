#define TOO_CLOSE 10
#define MAX_DISTANCE (TOO_CLOSE * 20)
#define BT_RX_PIN 9
#define BT_TX_PIN 10

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(BT_RX_PIN, BT_TX_PIN);

#include "buzzer.h"
#include "motor.h"
#include <NewPing.h>
#include "ultrasonicsensor.h"
#include "average.h"
#include "bluetooth.h"

#define ULTRASONIC_SENSOR_INIT A5,A4,MAX_DISTANCE

Wireless::packet pkt;
Bluetooth bluetooth;

class InBot {
  
  public:
    InBot() : buzzer(), motors(), ultrasonicSensor(ULTRASONIC_SENSOR_INIT), sensorAverage(MAX_DISTANCE) {
      init();
    }
    
    void init() {
      motors.stopWheels();
      state = STOPPED;
      startTime = millis();
    }
    

    
    void run() {
      
      bool haveRemoteCmd = bluetooth.getRemoteCommand(pkt);
      
      if (haveRemoteCmd) {
        process(pkt);
      }
       
    }
    
  protected:
    
      void process(Wireless::packet& pkt) { 
        
        if (pkt.comm == "PLAY") {
          char note = pkt.arg1.charAt(0);
          int beat = pkt.arg2.toInt();
          buzzer.playNote(note, beat);
        }
        
        if (pkt.comm == "FORWARD") {
          int time = pkt.arg1.toInt();
          int distance = pkt.arg2.toInt();
          motors.forward(time, distance);
          state = MOVING;
        }
        
        if (pkt.comm == "BACKWARD") {
          int time = pkt.arg1.toInt();
          int distance = pkt.arg2.toInt();
          motors.backward(time, distance);
          state = MOVING;
        }
        
        if (pkt.comm == "STOP") {
          motors.stopWheels();
          state = STOPPED;
        }
        
        if (pkt.comm == "LEFT") {
          int angle = pkt.arg1.toInt();
          motors.left(angle);
          state = TURNING;
        }
        
        if (pkt.comm == "RIGHT") {
          int angle = pkt.arg1.toInt();
          motors.right(angle);
          state = TURNING;
        }
        
      }
    
  private:
  
    Buzzer buzzer;
    Motor motors;
    UltrasonicSensor ultrasonicSensor;
    MovingAverage<unsigned int, 3> sensorAverage;
    
    enum state_t { STOPPED, MOVING, OBSTACLE, TURNING };
    state_t state;
    unsigned long startTime;
};
      
InBot inbot; 

void setup() {
  Serial.begin(9600);
  bluetooth.init();
  inbot.init();
}

void loop() {
  inbot.run();
}

