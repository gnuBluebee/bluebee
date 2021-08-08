#include <Arduino.h>

void SendDataToProcessing(
  float *dt,
  float *filtered_angle_x,
  float *filtered_angle_y,
  float *filtered_angle_z,
  float *roll_target_angle,
  float *pitch_target_angle,
  float *yaw_target_angle,
  float *throttle,
  float *motorA_speed,
  float *motorB_speed,
  float *motorC_speed,
  float *motorD_speed
) {
  Serial.print("DEL: ");
  Serial.print(*dt, DEC);
  Serial.print("#RPY: ");
  Serial.print(*filtered_angle_y, 2);
  Serial.print(",");
  Serial.print(*filtered_angle_x, 2);
  Serial.print(",");
  Serial.print(*filtered_angle_z, 2);

  Serial.print("#TARGET: ");
  Serial.print(*roll_target_angle, 2);
  Serial.print(",");
  Serial.print(*pitch_target_angle, 2);
  Serial.print(",");
  Serial.print(*yaw_target_angle, 2);
  Serial.print(",");
  Serial.print(*throttle, 2);

  Serial.print("#A");
  Serial.print(*motorA_speed, 2);
  Serial.print("#B");
  Serial.print(*motorB_speed, 2);
  Serial.print("#C");
  Serial.print(*motorC_speed, 2);
  Serial.print("#D");
  Serial.println(*motorD_speed, 2);
}