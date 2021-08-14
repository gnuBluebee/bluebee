#pragma once

#include <Arduino.h>
#include <Arduino_LSM9DS1.h>
#include <ArduinoBLE.h>
#include <mbed.h>
#include "dualPID.h"
#include "SendDataToProcessing.h"
#include "MotorSpeed.h"
#include "BluebeeDataType.h"
#include "calcFilteredYPR.h"
#include "calcYPRtoDualPID.h"

int calibAccelGyro();
int initDT();
int calcDT();
int initYPR();
void beacon_thread();
void FlightControl();

void calcMotorSpeed();
void checkMspPacket();
void printMspPacket();
int BeaconDetector();
