#include "motor.h"
#include <Arduino.h>

Motor::Motor() {
  pinMode(R_CTRL_1, OUTPUT);
  pinMode(R_CTRL_2, OUTPUT);
  pinMode(L_CTRL_1, OUTPUT);
  pinMode(L_CTRL_2, OUTPUT);
}

void Motor::forward(int time, int speed) {
  leftFwd(speed);
  rightFwd(speed);
  delay(time);
}

void Motor::backward(int time, int speed) {
  leftRev(speed);
  rightRev(speed);
  delay(time);
}

void Motor::stopWheels() {
  leftStop();
  rightStop();
}

void Motor::left(int time) {
  turnLeft(time, 255);
}

void Motor::right(int time) {
  turnRight(time, 255);
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

