#include "motor.h"
#include <Arduino.h>

Motor::Motor() {
  pinMode(R_CTRL_1, OUTPUT);
  pinMode(R_CTRL_2, OUTPUT);
  pinMode(L_CTRL_1, OUTPUT);
  pinMode(L_CTRL_2, OUTPUT);
}

void Motor::drive(int speed) {
  if (speed > 0) {
    leftFwd(speed);
    rightFwd(speed);
  }
  if (speed < 0) {
    leftRev(abs(speed));
    rightRev(abs(speed));
  }
  if (speed == 0) {
    leftStop();
    rightStop();
  }
}

void Motor::turn(int speed) {
  if (speed > 0) {
    leftFwd(speed);
    rightRev(speed);
  }
  if (speed < 0) {
    leftRev(speed);
    rightFwd(speed);
  }
  if (speed == 0) {
    leftStop();
    rightStop();
  }
}

int Motor::getSpeed() {
  return speed;
}

void Motor::leftFwd(int spd) {
  digitalWrite(L_CTRL_1, HIGH);
  digitalWrite(L_CTRL_2, LOW);
  analogWrite(PWM_L, spd);
}

void Motor::leftRev(int spd) {
  digitalWrite(L_CTRL_1, LOW);
  digitalWrite(L_CTRL_2, HIGH);
  analogWrite(PWM_L, spd);
}

void Motor::rightFwd(int spd) {
  digitalWrite(R_CTRL_1, HIGH);
  digitalWrite(R_CTRL_2, LOW);
  analogWrite(PWM_R, spd);
}

void Motor::rightRev(int spd) {
  digitalWrite(R_CTRL_1, LOW);
  digitalWrite(R_CTRL_2, HIGH);
  analogWrite(PWM_R, spd);
}

void Motor::leftStop() {
  digitalWrite(L_CTRL_1, LOW);
  digitalWrite(L_CTRL_2, LOW);
  analogWrite(PWM_L, 0);
}

void Motor::rightStop() {
  digitalWrite(R_CTRL_1, LOW);
  digitalWrite(R_CTRL_2, LOW);
  analogWrite(PWM_R, 0);
}

