#include "ElectricRayMotor.h"
#include <Arduino.h>

/******************************************************************************
Public functions for ElectricRayMotor
******************************************************************************/

ElectricRayMotor::ElectricRayMotor() {
  pinMode(R_CTRL_1, OUTPUT);
  pinMode(L_CTRL_1, OUTPUT);
  pinMode(PWM_L, OUTPUT);
  pinMode(PWM_R, OUTPUT);
}

void ElectricRayMotor::drive(int spd) { 
  if (spd > 0){
    leftFwd((byte)(abs(spd)));
    rightFwd((byte)(abs(spd)));
  } else {
    leftRev((byte)(abs(spd)));
    rightRev((byte)(abs(spd)));
  }
}

void ElectricRayMotor::stopped() {  
  leftStopped();
  rightStopped();
}

void ElectricRayMotor::turn(int spd) {
  if (spd > 0) {
    leftRev((byte)(abs(spd)));
    rightFwd((byte)(abs(spd)));
  } else {
    leftFwd((byte)(abs(spd)));
    rightRev((byte)(abs(spd)));
  }
}


void ElectricRayMotor::rightDrive(int spd) {
  if (spd < 0) {
    rightFwd((byte)(abs(spd)));
  } else {
    rightRev((byte)(abs(spd)));
  }
}

void ElectricRayMotor::leftDrive(int spd) {
  if (spd < 0) {
    leftFwd((byte)(abs(spd)));
  } else {
    leftRev((byte)(abs(spd)));
  }
}

void ElectricRayMotor::leftFwd(byte spd) {
  digitalWrite(L_CTRL_1, HIGH);
  analogWrite(PWM_L, spd);
}

void ElectricRayMotor::rightFwd(byte spd) {
  digitalWrite(R_CTRL_1, HIGH);
  analogWrite(PWM_R, spd);
}

void ElectricRayMotor::leftRev(byte spd) {
  digitalWrite(L_CTRL_1, LOW);
  analogWrite(PWM_L, spd);
}

void ElectricRayMotor::rightRev(byte spd) {
  digitalWrite(R_CTRL_1, LOW);
  analogWrite(PWM_R, spd);
}

void ElectricRayMotor::leftStopped() {
  digitalWrite(L_CTRL_1, LOW);
  analogWrite(PWM_L, 0);
}

void ElectricRayMotor::rightStopped() {
  digitalWrite(R_CTRL_1, LOW);
  analogWrite(PWM_R, 0);
}
