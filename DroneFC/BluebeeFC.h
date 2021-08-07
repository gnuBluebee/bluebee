#ifndef __BLUEBEEFC_H__
#define __BLUEBEEFC_H__

#include <Arduino.h>
#include <Arduino_LSM9DS1.h>
#include "dualPID.h"
#include "SendDataToProcessing.h"
#include "MotorSpeed.h"

int calibAccelGyro();
int initDT();
int calcDT();
int calcFilteredYPR();
int initYPR();

void calcYPRtoDualPID();
void calcMotorSpeed();
void checkMspPacket();
void printMspPacket();

#endif