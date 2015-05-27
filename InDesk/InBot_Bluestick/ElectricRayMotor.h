#ifndef ElectricRayMotor_h
#define ElectricRayMotor_h

#include <Arduino.h>

// Pin aliases for the motor controller.
#define L_CTRL_1 12
#define PWM_L 3

#define R_CTRL_1 11
#define PWM_R 5


enum WHEEL {LEFT, RIGHT, BOTH};

class ElectricRayMotor {
  
  public:
  
  // Constructor. Mainly sets up pins.
  ElectricRayMotor();
  // Drive in direction given by sign, at speed given by magnitude of the parameter.      
  void drive(int spd);
  // Pivot more or less in place. Turns motors in opposite directions.
  // Positive values correspond to anti-clockwise rotation.
  void turn(int spd);  
  // Drive just the left motor, as drive().
  void rightDrive(int spd); 
  // Drive just the right motor, as drive().
  void leftDrive(int spd);  
  // Stop motors, but slow halt
  void stopped();      
       
  
  private:
    
    void leftFwd(byte speed); 
    void leftRev(byte speed);
    void rightFwd(byte speed);
    void rightRev(byte speed);      
    void leftStopped();      
    void rightStopped(); 
};

#endif
