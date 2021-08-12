#include <Arduino.h>
#include "BluebeeDataType.h"

void SendDataToProcessing(FlightData *fdata) {
  Serial.print("DEL: ");
  Serial.print(fdata->dt, DEC);
  Serial.print("#RPY: ");
  Serial.print(fdata->filtered_angle_y, 2);
  Serial.print(",");
  Serial.print(fdata->filtered_angle_x, 2);
  Serial.print(",");
  Serial.print(fdata->filtered_angle_z, 2);

  Serial.print("#TARGET: ");
  Serial.print(fdata->roll_target_angle, 2);
  Serial.print(",");
  Serial.print(fdata->pitch_target_angle, 2);
  Serial.print(",");
  Serial.print(fdata->yaw_target_angle, 2);
  Serial.print(",");
  Serial.print(fdata->throttle, 2);

  Serial.print("#A");
  Serial.print(fdata->motorA_speed, 2);
  Serial.print("#B");
  Serial.print(fdata->motorB_speed, 2);
  Serial.print("#C");
  Serial.print(fdata->motorC_speed, 2);
  Serial.print("#D");
  Serial.println(fdata->motorD_speed, 2);
}