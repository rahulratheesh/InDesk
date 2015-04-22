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
    InBot() : motors(), ultrasonicSensor(ULTRASONIC_SENSOR_INIT), sensorAverage(MAX_DISTANCE) {
      init();
    }
    
    void init() {
      motors.drive(0);
      state = STOPPED;
      startTime = millis();
    }
    

    
    void run() {
//      int distance = sensorAverage.add(ultrasonicSensor.getDistance());
//      if (distance <= TOO_CLOSE) {
//        state = OBSTACLE;
//        motors.drive(0);
//      }
//      else {
//        state = MOVING;
//        motors.drive(255);
//      }
  
//      char notes[] = "ccggaag-ffeeddc "; // a space represents a rest
//      int beats[] = { 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2, 4 };  
//      for (int i = 0; i < 16; i++) {
//        buzzer.playNote(notes[i], beats[i]);
//      }

      bool haveRemoteCmd = bluetooth.getRemoteCommand(pkt);
      if (haveRemoteCmd) {
        process(pkt);
      }
       
    }
    
  protected:
    
    
//    void turn(int angle) {
//      if (angle > 0) {
//        motors.drive(200);
//      } else if (angle < 0) {
//        motors.drive(-200);
//      } else {
//        motors.drive(0);
//      }
//      startTime = millis();
//      state = TURNING;
//    }
//    
//    bool moving() { 
//      return (state == MOVING); 
//    }
//    
//    bool turning() { 
//      return (state == TURNING); 
//    }
//    
//    bool stopped() { 
//      return (state == STOPPED); 
//    }

      void process(Wireless::packet& pkt) { 
        if (pkt.comm == "PLAY") {
          char note = pkt.arg1.charAt(0);
          int beat = pkt.arg2.toInt();
          buzzer.playNote(note, beat);
        }
      }
    
  private:
    Buzzer buzzer;
    Motor motors;
    UltrasonicSensor ultrasonicSensor;
    MovingAverage<unsigned int, 3> sensorAverage;
    enum state_t { STOPPED, MOVING, OBSTACLE, TURNING, TURNED };
    state_t state;
    unsigned long startTime;
};
      
InBot inbot; 

void initBluetooth() {
    BTSerial.begin(38400);
    // set the bluetooth work in slave mode
    BTSerial.print("\r\n+STWMOD=0\r\n");
    // set the bluetooth name as "SeeedBTSlave"
    BTSerial.print("\r\n+STNA=SeeedBTSlave\r\n");
    // Permit Paired device to connect me
    BTSerial.print("\r\n+STOAUT=1\r\n"); 
    // Auto-connection should be forbidden
    BTSerial.print("\r\n+STAUTO=0\r\n"); 
    // This delay is required.
    delay(2000); 
    // make the slave bluetooth inquirable
    BTSerial.print("\r\n+INQ=1\r\n"); 
    Serial.println("The slave bluetooth is inquirable!");
    // This delay is required.
    delay(2000); 
    BTSerial.flush(); 
}

void setup() {
  Serial.begin(9600);
  initBluetooth();
  inbot.init();
}

void loop() {
  inbot.run();
}

