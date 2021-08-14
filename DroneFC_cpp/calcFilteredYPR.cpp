#include "BluebeeDataType.h"
#include <Arduino.h>

int calcFilteredYPR(
    SensorData *sdata,
    PostureAngle *angle,
    float *dt
) {
  
  // 가속도 YPR 값 구하기
  float accel_angle_x = 0, accel_angle_y = 0;
  float _accel_x, _accel_y, _accel_z;
  float _accel_xz, _accel_yz;
  const float RADIANS_TO_DEGREES = 180 / 3.14159;

  _accel_x = sdata->accel_x - sdata->baseAcX;
  _accel_y = sdata->accel_y - sdata->baseAcY;
  _accel_z = sdata->accel_z + (1 - sdata->baseAcZ);

  _accel_yz = sqrt(pow(_accel_y, 2) + pow(_accel_z, 2));
  accel_angle_y = atan(-_accel_x / _accel_yz) * RADIANS_TO_DEGREES;

  _accel_xz = sqrt(pow(_accel_x, 2) + pow(_accel_z, 2));
  accel_angle_x = atan(_accel_y / _accel_xz) * RADIANS_TO_DEGREES;
  
  // 자이로 센서 보정값 적용
  sdata->gyro_x = sdata->gyro_x - sdata->baseGyX;
  sdata->gyro_y = sdata->gyro_y - sdata->baseGyY;
  sdata->gyro_z =sdata->gyro_z - sdata->baseGyZ;

  // 상보필터
  const float ALPHA = 0.96;
  float tmp_angle_x, tmp_angle_y, tmp_angle_z;

  tmp_angle_x = angle->roll + sdata->gyro_x * (*dt);
  tmp_angle_y = angle->pitch + sdata->gyro_y * (*dt);
  tmp_angle_z = angle->yaw + sdata->gyro_z * (*dt);

  angle->roll =
    ALPHA * tmp_angle_x + (1.0 - ALPHA) * accel_angle_x;
  angle->pitch =
    ALPHA * tmp_angle_y + (1.0 - ALPHA) * accel_angle_y;
  angle->yaw = tmp_angle_z;

  return 0;
}