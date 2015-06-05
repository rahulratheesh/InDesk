#include "motor.h"
#include <Arduino.h>

Motor::Motor() {
  pinMode(R_CTRL_1, OUTPUT);
  pinMode(L_CTRL_1, OUTPUT);
  pinMode(PWM_L, OUTPUT);
  pinMode(PWM_R, OUTPUT);
}

void Motor::forward(int time, int speed) {
  leftFwd(speed);
  rightFwd(speed);
  delay(time);
  stopWheels();
}

void Motor::backward(int time, int speed) {
  leftRev(speed);
  rightRev(speed);
  delay(time);
  stopWheels();
}

void Motor::stopWheels() {
  leftStop();
  rightStop();
}

void Motor::left(int time) {
  turnLeft(time, 255);
  stopWheels();
}

void Motor::right(int time) {
  turnRight(time, 255);
  stopWheels();
}


void Motor::leftFwd(int spd) {
  digitalWrite(L_CTRL_1, HIGH);
  analogWrite(PWM_L, spd);
}

void Motor::leftRev(int spd) {
  digitalWrite(L_CTRL_1, LOW);
  analogWrite(PWM_L, spd);
}

void Motor::rightFwd(int spd) {
  digitalWrite(R_CTRL_1, HIGH);
  analogWrite(PWM_R, spd);
}

void Motor::rightRev(int spd) {
  digitalWrite(R_CTRL_1, LOW);
  analogWrite(PWM_R, spd);
}

void Motor::leftStop() {
  digitalWrite(L_CTRL_1, LOW);
  analogWrite(PWM_L, 0);
}

void Motor::rightStop() {
  digitalWrite(R_CTRL_1, LOW);
  analogWrite(PWM_R, 0);
}

void Motor::turnLeft(int time, int speed) {
  rightFwd(speed);
  leftStop();
  delay(time);
}

void Motor::turnRight(int time, int speed) {
  leftFwd(speed);
  rightStop();
  delay(time);
}

