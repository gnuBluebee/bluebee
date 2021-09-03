#include "BluebeeDataType.h"
#include "dualPID.h"

void calcYPRtoDualPID(
  ControlValue *cv_roll,
  ControlValue *cv_pitch,
  ControlValue *cv_yaw,
  SensorData *sdata,
  PostureAngle *angle,
  float *dt
) {

  cv_roll->angle_in = angle->roll;
  cv_roll->rate_in = -(sdata->gyro_x);

  dualPID(cv_roll, dt);

  cv_pitch->angle_in = angle->pitch;
  cv_pitch->rate_in = -(sdata->gyro_y);

  dualPID(cv_pitch, dt);

  cv_yaw->angle_in = angle->yaw;
  cv_yaw->rate_in = (sdata->gyro_z);

  dualPID(cv_yaw, dt);
}