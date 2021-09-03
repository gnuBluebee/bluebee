#include <Arduino.h>

#ifndef THROTTLE_MIN
#define THROTTLE_MIN 0
#endif

// 아두이노 모터제어용 핀번호 선언
static int motorA_pin = 7;
static int motorB_pin = 9;
static int motorC_pin = 8;
static int motorD_pin = 12;

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
  byte motorA, motorB, motorC,motorD;
  motorA = (byte)*motorA_speed;
  motorB = (byte)*motorB_speed;
  motorC = (byte)*motorC_speed;
  motorD = (byte)*motorD_speed;

  analogWrite(motorA_pin, motorA);
  analogWrite(motorB_pin, motorB);
  analogWrite(motorC_pin, motorC);
  analogWrite(motorD_pin, motorD);
}