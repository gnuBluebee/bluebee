#include <BluebeeFC.h>

#define THROTTLE_MAX 255
#define THROTTLE_MIN 0

// 수신기 데이터값
uint8_t mspPacket[11];

// 센서 초기값
float baseAcX, baseAcY, baseAcZ;
float baseGyX, baseGyY, baseGyZ;

// 자이로 센서에서 수신 받은 데이터
float accel_x, accel_y, accel_z;
float gyro_x, gyro_y, gyro_z;
float mag_x, mag_y, mag_z;

// 초기각도 값
float base_roll_target_angle = 0;
float base_pitch_target_angle = 0;
float base_yaw_target_angle = 0;

// dt
unsigned long t_now;
unsigned long t_prev;
float dt = 0.0;

// 오일러각
float accel_angle_x, accel_angle_y, accel_angle_z;
// 상보필터로 구한 각 = 최종각
float filtered_angle_x, filtered_angle_y, filtered_angle_z;

// 제어값
float roll_target_angle = 0.0;
float roll_angle_in;
float roll_rate_in;
float roll_stabilize_kp = 1;
float roll_stabilize_ki = 0;
float roll_rate_kp = 1;
float roll_rate_ki = 0;
float roll_stabilize_iterm;
float roll_rate_iterm;
float roll_output;

float pitch_target_angle = 0.0;
float pitch_angle_in;
float pitch_rate_in;
float pitch_stabilize_kp = 1;
float pitch_stabilize_ki = 0;
float pitch_rate_kp = 1;
float pitch_rate_ki = 0;
float pitch_stabilize_iterm;
float pitch_rate_iterm;
float pitch_output;

float yaw_target_angle = 0.0;
float yaw_angle_in;
float yaw_rate_in;
float yaw_stabilize_kp = 1;
float yaw_stabilize_ki = 0;
float yaw_rate_kp = 1;
float yaw_rate_ki = 0;
float yaw_stabilize_iterm;
float yaw_rate_iterm;
float yaw_output;

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
  IMU.readAcceleration(accel_x, accel_y, accel_z);
  IMU.readGyroscope(gyro_x, gyro_y, gyro_z);
  IMU.readMagneticField(mag_x, mag_y, mag_z);
  calcDT();
  calcFilteredYPR();

  calcYPRtoDualPID();
  calcMotorSpeed();
  checkMspPacket();

  updateMotorSpeed(
  &motorA_speed,
  &motorB_speed,
  &motorC_speed,
  &motorD_speed
  );

  SendDataToProcessing( 
  &dt,
  &filtered_angle_x,
  &filtered_angle_y,
  &filtered_angle_z,
  &roll_target_angle,
  &pitch_target_angle,
  &yaw_target_angle,
  &throttle,
  &motorA_speed,
  &motorB_speed,
  &motorC_speed,
  &motorD_speed
);

}


int calibAccelGyro() {
  float sumAcX = 0, sumAcY = 0, sumAcZ = 0;
  float sumGyX = 0, sumGyY = 0, sumGyZ = 0;

  for (int i = 0; i < 100; i++) {
    IMU.readAcceleration(accel_x, accel_y, accel_z);
    IMU.readGyroscope(gyro_x, gyro_y, gyro_z);
    sumAcX += accel_x, sumAcY += accel_y, sumAcZ += accel_z;
    sumGyX += gyro_x, sumGyY += gyro_y, sumGyZ += gyro_z;
    delay(10);
  }

  baseAcX = sumAcX / 100;
  baseAcY = sumAcY / 100;
  baseAcZ = sumAcZ / 100;

  baseGyX = sumGyX / 100;
  baseGyY = sumGyY / 100;
  baseGyZ = sumGyZ / 100;

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
  float _accel_x, _accel_y, _accel_z;
  float _accel_xz, _accel_yz;
  const float RADIANS_TO_DEGREES = 180 / 3.14159;

  _accel_x = accel_x - baseAcX;
  _accel_y = accel_y - baseAcY;
  _accel_z = accel_z + (1 - baseAcZ);

  _accel_yz = sqrt(pow(_accel_y, 2) + pow(_accel_z, 2));
  accel_angle_y = atan(-_accel_x / _accel_yz) * RADIANS_TO_DEGREES;

  _accel_xz = sqrt(pow(_accel_x, 2) + pow(_accel_z, 2));
  accel_angle_x = atan(_accel_y / _accel_xz) * RADIANS_TO_DEGREES;

  accel_angle_z = 0;
  
  // 자이로 센서 보정값 적용
  gyro_x = gyro_x - baseGyX;
  gyro_y = gyro_y - baseGyY;
  gyro_z = gyro_z - baseGyZ;

  // 상보필터
  const float ALPHA = 0.96;
  float tmp_angle_x, tmp_angle_y, tmp_angle_z;

  tmp_angle_x = filtered_angle_x + gyro_x * dt;
  tmp_angle_y = filtered_angle_y + gyro_y * dt;
  tmp_angle_z = filtered_angle_z + gyro_z * dt;

  filtered_angle_x =
    ALPHA * tmp_angle_x + (1.0 - ALPHA) * accel_angle_x;
  filtered_angle_y =
    ALPHA * tmp_angle_y + (1.0 - ALPHA) * accel_angle_y;
  filtered_angle_z = tmp_angle_z;

  return 0;
}


int initYPR() {
  for (int i = 0; i < 10; i++) {
    IMU.readAcceleration(accel_x, accel_y, accel_z);
    IMU.readGyroscope(gyro_x, gyro_y, gyro_z);
    IMU.readMagneticField(mag_x, mag_y, mag_z);
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

  roll_target_angle = base_roll_target_angle;
  pitch_target_angle = base_pitch_target_angle;
  yaw_target_angle = base_yaw_target_angle;

  return 0;
}


void calcMotorSpeed() {
  motorA_speed = (throttle == 0) ? 0:
    throttle + yaw_output + roll_output + pitch_output; //뒷 부분에 + ??를 붙여 모터 보정
  motorB_speed = (throttle == 0) ? 0:
    throttle - yaw_output - roll_output + pitch_output;
  motorC_speed = (throttle == 0) ? 0:
    throttle + yaw_output - roll_output - pitch_output;
  motorD_speed = (throttle == 0) ? 0:
    throttle - yaw_output + roll_output - pitch_output;
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

          roll_target_angle = base_roll_target_angle;
          pitch_target_angle = base_pitch_target_angle;
          yaw_target_angle = base_yaw_target_angle;

          roll_target_angle += (mspPacket[5] - 125);
          pitch_target_angle += (mspPacket[6] - 125);
          yaw_target_angle += (mspPacket[7] - 125);
          
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

  roll_angle_in = filtered_angle_y;
  roll_rate_in = gyro_y;
  dualPID(&roll_target_angle ,
    &roll_angle_in, 
    &roll_rate_in, 
    &roll_stabilize_kp, 
    &roll_stabilize_ki, 
    &roll_rate_kp, 
    &roll_rate_ki, 
    &roll_stabilize_iterm, 
    &roll_rate_iterm,
    &roll_output,
    &dt);

  pitch_angle_in = filtered_angle_x;
  pitch_rate_in = gyro_x;
  dualPID(&pitch_target_angle, 
    &pitch_angle_in,  
    &pitch_rate_in,
    &pitch_stabilize_kp, 
    &pitch_stabilize_ki, 
    &pitch_rate_kp, 
    &pitch_rate_ki, 
    &pitch_stabilize_iterm, 
    &pitch_rate_iterm, 
    &pitch_output,
    &dt);

  yaw_angle_in = filtered_angle_z;
  yaw_rate_in = gyro_z;
  dualPID(&yaw_target_angle, 
    &yaw_angle_in, 
    &yaw_rate_in, 
    &yaw_stabilize_kp, 
    &yaw_stabilize_ki, 
    &yaw_rate_kp, 
    &yaw_rate_ki, 
    &yaw_stabilize_iterm, 
    &yaw_rate_iterm, 
    &yaw_output,
    &dt);
}
