#include "BluebeeDataType.h"

void calcYPRtoDualPID(
  ControlValue *cv_roll,
  ControlValue *cv_pitch,
  ControlValue *cv_yaw,
  SensorData *sdata,
  PostureAngle *angle,
  float *dt
);