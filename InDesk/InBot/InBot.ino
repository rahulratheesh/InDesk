#include <QueueList.h>

#define LOGGING
#include "logging.h"

#define TOO_CLOSE 10
#define MAX_DISTANCE (TOO_CLOSE * 20)
#define BT_RX_PIN 2
#define BT_TX_PIN 1
#define ULTRASONIC_SENSOR_INIT 9,10,MAX_DISTANCE

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(BT_RX_PIN, BT_TX_PIN);

#include "buzzer.h"
#include "motor.h"
#include <NewPing.h>
#include "ultrasonicsensor.h"
#include "average.h"
#include "bluetooth.h"

Wireless::packet pkt;
Bluetooth bluetooth;

bool obstacleDetection;
bool obstacle;
QueueList <String> queue;

class InBot {
  
  public:
  

    
    InBot() : buzzer(), motors(), ultrasonicSensor(ULTRASONIC_SENSOR_INIT), sensorAverage(MAX_DISTANCE) {
      init();
    }
    
    void init() {
      motors.stopWheels();
      state = STOPPED;
      startTime = millis();
      obstacleDetection = false;
      obstacle = false;
    }
    

    
    void run() {
      
      distance = ultrasonicSensor.getDistance();

      if (distance < TOO_CLOSE) {
        obstacle = true;
      } else {
        obstacle = false;
      }
      
      bool haveRemoteCmd = bluetooth.getRemoteCommand(pkt);
      
      if (haveRemoteCmd) {
        process(pkt);
      }
       
    }
    
  protected:
    
      void process(Wireless::packet& pkt) { 
        
         if (obstacleDetection && obstacle) {
           return;
         }
         
        if (pkt.comm == "PLAY") {
          char note = pkt.arg1.charAt(0);
          int beat = pkt.arg2.toInt();
          buzzer.playNote(note, beat);
        }
        
        if (pkt.comm == "FORWARD") {
          int time = pkt.arg1.toInt() * 100;
          int distance = pkt.arg2.toInt();
          motors.forward(time, distance);
          state = MOVING;
        }
        
        if (pkt.comm == "BACKWARD") {
          int time = pkt.arg1.toInt() * 100;
          int distance = pkt.arg2.toInt();
          motors.backward(time, distance);
          state = MOVING;
        }
        
        if (pkt.comm == "STOP") {
          motors.stopWheels();
          state = STOPPED;
        }
        
        if (pkt.comm == "LEFT") {
          int angle = pkt.arg1.toInt() * 10;
          motors.left(angle);
          state = TURNING;
        }
        
        if (pkt.comm == "RIGHT") {
          int angle = pkt.arg1.toInt() * 10;
          motors.right(angle);
          state = TURNING;
        }
                
        if (pkt.comm == "OBSTACLEON") {
          obstacleDetection = true;
        }
        
        if (pkt.comm == "OBSTACLEOFF") {
          obstacleDetection = false;
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
    unsigned int distance;
    
};
      
InBot inbot; 

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  inbot.init();
}

void loop() {
  inbot.run();
}

