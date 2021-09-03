#pragma once

typedef struct
{
  float dt;
  float filtered_angle_x;
  float filtered_angle_y;
  float filtered_angle_z;
  float roll_target_angle;
  float pitch_target_angle;
  float yaw_target_angle;
  float throttle;
  float motorA_speed;
  float motorB_speed;
  float motorC_speed;
  float motorD_speed;

}FlightData;
typedef struct
{ 
  float target;
  float angle_in;
  float rate_in;
  float stabilize_kp;
  float stabilize_ki;
  float rate_kp;
  float rate_ki;
  float rate_kd;
  float stabilize_iterm;
  float rate_iterm;
  float output;
  float dt;
}ControlValue;

typedef struct 
{
  float baseAcX;
  float baseAcY; 
  float baseAcZ;
  float baseGyX; 
  float baseGyY; 
  float baseGyZ;

  float accel_x; 
  float accel_y; 
  float accel_z;
  float gyro_x; 
  float gyro_y; 
  float gyro_z;
  
}SensorData;

typedef struct
{
  float roll;
  float pitch;
  float yaw;
  
}PostureAngle;