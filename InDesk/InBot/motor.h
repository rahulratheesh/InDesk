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
    
    /**
     * @brief Drives the motor.
     * @param speed The new speed of the motor.
     * Valid values are between -255 and 255.
     * Use positive values to run the motor forward,
     * negative values to run it backward and zero to stop the motor.
    */
    void drive(int speed);
    
    /**
     * @brief Turns the motor.
     * @param angle The angle of turn.
     * Valid values are between -255 and 255.
     * Use positive values to turn the motor right,
     * negative values to turn it left and zero to stop the motor.
    */
    void turn(int speed);
    
    /**
    * @brief Return the current speed of the motor.
    * @return The current speed of the motor with range -255 to 255.
    */
    int getSpeed();
    
  private:
    int speed;
    
    void leftFwd(int speed); 
    void leftRev(int speed);
    void rightFwd(int speed);
    void rightRev(int speed);
    void leftStop();
    void rightStop();
};

#endif
