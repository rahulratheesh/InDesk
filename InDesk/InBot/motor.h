#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

// Pin aliases for the motor controller.
#define L_CTRL_1 2
#define L_CTRL_2 4
#define PWM_L 3

#define R_CTRL_1 7
#define R_CTRL_2 5
#define PWM_R 6

class Motor
{
  public:
    
    Motor();
    
    void forward(int time, int speed);
    void backward(int time, int speed);
    void stopWheels();
    void left(int time);
    void right(int time);
    
  private:
    
    void leftFwd(int speed); 
    void leftRev(int speed);
    void rightFwd(int speed);
    void rightRev(int speed);
    void leftStop();
    void rightStop();
    void turnLeft(int time, int speed);
    void turnRight(int time, int speed);
};

#endif
