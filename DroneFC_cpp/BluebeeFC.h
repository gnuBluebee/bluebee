#pragma once

#include <Arduino.h>
#include <Arduino_LSM9DS1.h>
#include "dualPID.h"
#include "SendDataToProcessing.h"
#include "MotorSpeed.h"
#include "BluebeeDataType.h"

int calibAccelGyro();
int initDT();
int calcDT();
int calcFilteredYPR();
int initYPR();

void calcYPRtoDualPID();
void calcMotorSpeed();
void checkMspPacket();
void printMspPacket();
