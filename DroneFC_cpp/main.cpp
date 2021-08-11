#include <BluebeeFC.h>

#define THROTTLE_MAX 255
#define THROTTLE_MIN 0



// 수신기 데이터값
uint8_t mspPacket[11];

// 센서 데이터 및 보정 데이터 구조체
SensorData sdata = {0.0, };
// 비행 데이터 구조체
FlightData fdata = {0.0, };
//제어 관련 데이터 구조체
ControlValue cv_roll = {0.0, };
ControlValue cv_pitch = {0.0, };
ControlValue cv_yaw = {0.0, };

// dt
unsigned long t_now;
unsigned long t_prev;
float dt = 0.0;

// 상보필터로 구한 각 = 최종각
float filtered_angle_x, filtered_angle_y, filtered_angle_z;

// 초기각도 값 
float base_roll_target_angle = 0;
float base_pitch_target_angle = 0;
float base_yaw_target_angle = 0;



// 제어값
/*
float roll_target_angle = 0.0;
float roll_angle_in;
float roll_rate_in;
float roll_stabilize_kp = 3;
float roll_stabilize_ki = 0;
float roll_rate_kp = 1;
float roll_rate_ki = 0;
float roll_stabilize_iterm;
float roll_rate_iterm;
float roll_output;

float pitch_target_angle = 0.0;
float pitch_angle_in;
float pitch_rate_in;
float pitch_stabilize_kp = 3;
float pitch_stabilize_ki = 0;
float pitch_rate_kp = 1;
float pitch_rate_ki = 0;
float pitch_stabilize_iterm;
float pitch_rate_iterm;
float pitch_output;

float yaw_target_angle = 0.0;
float yaw_angle_in;
float yaw_rate_in;
float yaw_stabilize_kp = 0;
float yaw_stabilize_ki = 0;
float yaw_rate_kp = 1;
float yaw_rate_ki = 0;
float yaw_stabilize_iterm;
float yaw_rate_iterm;
float yaw_output;
*/

float throttle = 0.0;
float motorA_speed;
float motorB_speed; 
float motorC_speed;
float motorD_speed;

// MotorSpeed.cpp 에서 extern
int motorA_pin = 8;
int motorB_pin = 9;
int motorC_pin = 7;
int motorD_pin = 12;

void setup() {

  // 제어기 게인값 설정
  cv_roll.stabilize_kp = 3;
  cv_roll.rate_kp = 1;
  cv_roll.rate_ki = 0;
  cv_pitch.stabilize_kp = 3;
  cv_pitch.rate_kp = 1;
  cv_pitch.rate_ki = 0;
  cv_yaw.stabilize_kp = 0;
  cv_yaw.rate_kp = 1;
  cv_yaw.rate_ki = 0;

  Serial.begin(115200);
  Serial1.begin(9600);
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  calibAccelGyro();
  initDT();
  initYPR();
}

void loop() {
  IMU.readAcceleration(sdata.accel_x, sdata.accel_y, sdata.accel_z);
  IMU.readGyroscope(sdata.gyro_x, sdata.gyro_y, sdata.gyro_z);

  calcDT();
  calcFilteredYPR();

  cv_roll.stabilize_kp = 3;
  cv_roll.rate_kp = 1;
  cv_roll.rate_ki = 0;
  calcYPRtoDualPID();
  calcMotorSpeed();
  checkMspPacket();

  updateMotorSpeed(
  &motorA_speed,
  &motorB_speed,
  &motorC_speed,
  &motorD_speed
  );

  // FlightData 구조체 데이터 초기화
  fdata.dt = dt;
  fdata.filtered_angle_x = filtered_angle_x;
  fdata.filtered_angle_y = filtered_angle_y;
  fdata.filtered_angle_z = filtered_angle_z;
  fdata.roll_target_angle = cv_roll.target;
  fdata.pitch_target_angle =cv_pitch.target;
  fdata.yaw_target_angle = cv_yaw.target;
  fdata.throttle = throttle;
  fdata.motorA_speed = motorA_speed;
  fdata.motorB_speed =motorB_speed;
  fdata.motorC_speed = motorC_speed;
  fdata.motorD_speed = motorD_speed;

  SendDataToProcessing(&fdata);

}


int calibAccelGyro() {
  float sumAcX = 0, sumAcY = 0, sumAcZ = 0;
  float sumGyX = 0, sumGyY = 0, sumGyZ = 0;

  for (int i = 0; i < 2000; i++) {
    IMU.readAcceleration(sdata.accel_x, sdata.accel_y, sdata.accel_z);
    IMU.readGyroscope(sdata.gyro_x, sdata.gyro_y, sdata.gyro_z);
    
    sumAcX += sdata.accel_x, sumAcY += sdata.accel_y, sumAcZ += sdata.accel_z;
    sumGyX += sdata.gyro_x, sumGyY += sdata.gyro_y, sumGyZ += sdata.gyro_z;
    delay(1);
  }

  sdata.baseAcX = sumAcX / 2000;
  sdata.baseAcY = sumAcY / 2000;
  sdata.baseAcZ = sumAcZ / 2000;
  sdata.baseGyX = sumGyX / 2000;
  sdata.baseGyY = sumGyY / 2000;
  sdata.baseGyZ = sumGyZ / 2000;

  return 0;
}

int initDT() {
  t_prev = micros();

  return 0;
}

int calcDT() {
  t_now = micros();
  dt = (t_now - t_prev) / 1000000.0;
  t_prev = t_now;

  return 0;
}


int calcFilteredYPR() {
  
  // 가속도 YPR 값 구하기
  float accel_angle_x = 0, accel_angle_y = 0, accel_angle_z = 0;
  float _accel_x, _accel_y, _accel_z;
  float _accel_xz, _accel_yz;
  const float RADIANS_TO_DEGREES = 180 / 3.14159;

  _accel_x = sdata.accel_x - sdata.baseAcX;
  _accel_y = sdata.accel_y - sdata.baseAcY;
  _accel_z = sdata.accel_z + (1 - sdata.baseAcZ);

  _accel_yz = sqrt(pow(_accel_y, 2) + pow(_accel_z, 2));
  accel_angle_y = atan(-_accel_x / _accel_yz) * RADIANS_TO_DEGREES;

  _accel_xz = sqrt(pow(_accel_x, 2) + pow(_accel_z, 2));
  accel_angle_x = atan(_accel_y / _accel_xz) * RADIANS_TO_DEGREES;

  accel_angle_z = 0;
  
  // 자이로 센서 보정값 적용
  sdata.gyro_x = sdata.gyro_x - sdata.baseGyX;
  sdata.gyro_y = sdata.gyro_y - sdata.baseGyY;
  sdata.gyro_z =sdata. gyro_z - sdata.baseGyZ;

  // 상보필터
  const float ALPHA = 0.96;
  float tmp_angle_x, tmp_angle_y, tmp_angle_z;

  tmp_angle_x = filtered_angle_x + sdata.gyro_x * dt;
  tmp_angle_y = filtered_angle_y + sdata.gyro_y * dt;
  tmp_angle_z = filtered_angle_z + sdata.gyro_z * dt;

  filtered_angle_x =
    ALPHA * tmp_angle_x + (1.0 - ALPHA) * accel_angle_x;
  filtered_angle_y =
    ALPHA * tmp_angle_y + (1.0 - ALPHA) * accel_angle_y;
  filtered_angle_z = tmp_angle_z;

  return 0;
}


int initYPR() {


  for (int i = 0; i < 10; i++) {
    IMU.readAcceleration(sdata.accel_x, sdata.accel_y, sdata.accel_z);
    IMU.readGyroscope(sdata.gyro_x, sdata.gyro_y, sdata.gyro_z);

    calcDT();
    calcFilteredYPR();

    base_roll_target_angle += filtered_angle_y;
    base_pitch_target_angle += filtered_angle_x;
    base_yaw_target_angle += filtered_angle_z;

    delay(100);

  }

  base_roll_target_angle /= 10;
  base_pitch_target_angle /= 10;
  base_yaw_target_angle /= 10;

  cv_roll.target = base_roll_target_angle;
  cv_pitch.target = base_pitch_target_angle;
  cv_yaw.target = base_yaw_target_angle;

  return 0;
}


void calcMotorSpeed() {
  motorA_speed = (throttle == 0) ? 0:
    throttle + cv_yaw.output - cv_roll.output - cv_pitch.output; //뒷 부분에 + ??를 붙여 모터 보정
  motorB_speed = (throttle == 0) ? 0:
    throttle - cv_yaw.output + cv_roll.output - cv_pitch.output;
  motorC_speed = (throttle == 0) ? 0:
    throttle + cv_yaw.output + cv_roll.output + cv_pitch.output;
  motorD_speed = (throttle == 0) ? 0:
    throttle - cv_yaw.output - cv_roll.output + cv_pitch.output;
  //float throttle = 0;

  if (motorA_speed < 0) motorA_speed = 0;
  if (motorA_speed > 255) motorA_speed = 255;
  if (motorB_speed < 0) motorB_speed = 0;
  if (motorB_speed > 255) motorB_speed = 255;
  if (motorC_speed < 0) motorC_speed = 0;
  if (motorC_speed > 255) motorA_speed = 255;
  if (motorD_speed < 0) motorD_speed = 0;
  if (motorD_speed > 255) motorD_speed = 255;
}

void checkMspPacket() {

  static uint32_t cnt;

  if (Serial1.available() > 0) {
    while (Serial1.available() > 0) {
      uint8_t mspData = Serial1.read();
      if (mspData == '$') cnt = 0;
      else cnt++;

      mspPacket[cnt] = mspData;

      if (cnt == 10) {
        //printMspPacket();
        if (mspPacket[4] == 150) {
          throttle = mspPacket[8];

          cv_roll.target = base_roll_target_angle;
          cv_pitch.target = base_pitch_target_angle;
          cv_yaw.target = base_yaw_target_angle;

          cv_roll.target -= (float)(mspPacket[5] - 125) * 20/125;
          cv_pitch.target += (float)(mspPacket[6] - 125) * 20/125;
          cv_yaw.target -= (float)(mspPacket[7] - 125) * 20/125;
          
        }
      }
    }
  }
}
void printMspPacket() {
  Serial.print(Serial1.available());
  Serial.print(",");
  Serial.print((char)mspPacket[0]);
  Serial.print((char)mspPacket[1]);
  Serial.print((char)mspPacket[2]);
  Serial.print(mspPacket[3]);
  Serial.print(mspPacket[4]);
  Serial.print(mspPacket[5]);
  Serial.print(mspPacket[6]);
  Serial.print(mspPacket[7]);
  Serial.println(mspPacket[8]);

}

void calcYPRtoDualPID() {

  cv_roll.angle_in = filtered_angle_x;
  cv_roll.rate_in = -sdata.gyro_x;

  dualPID(&cv_roll, &dt);

  cv_pitch.angle_in = filtered_angle_y;
  cv_pitch.rate_in = -sdata.gyro_y;

  dualPID(&cv_pitch, &dt);

  cv_yaw.angle_in = filtered_angle_z;
  cv_yaw.rate_in = sdata.gyro_z;

  dualPID(&cv_yaw, &dt);
}
