#include <Arduino.h>

#ifndef THROTTLE_MIN
#define THROTTLE_MIN 0
#endif

// main.c;
extern int motorA_pin;
extern int motorB_pin;
extern int motorC_pin;
extern int motorD_pin;

void initMotorSpeed() {
  analogWrite(motorA_pin, THROTTLE_MIN);
  analogWrite(motorB_pin, THROTTLE_MIN);
  analogWrite(motorC_pin, THROTTLE_MIN);
  analogWrite(motorD_pin, THROTTLE_MIN);
}

void updateMotorSpeed(
  float *motorA_speed,
  float *motorB_speed,
  float *motorC_speed,
  float *motorD_speed
){
  analogWrite(motorA_pin, *motorA_speed);
  analogWrite(motorB_pin, *motorB_speed);
  analogWrite(motorC_pin, *motorC_speed);
  analogWrite(motorD_pin, *motorD_speed);
}