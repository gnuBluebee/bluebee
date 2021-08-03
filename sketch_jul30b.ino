#include <Arduino_LSM9DS1.h>

const int MPU_addr = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

int calibAccelGyro();
int initDT();
int calcDT();
int senddata();
int calcAccelYPR();
int calcGyroYPR();
int calcFilteredYPR();
int initYPR();

// 센서 초기값
float baseAcX, baseAcY, baseAcZ;
float baseGyX, baseGyY, baseGyZ;

// 자이로 센서에서 수신 받은 데이터
float accel_x, accel_y, accel_z;
float gyro_x, gyro_y, gyro_z;
float mag_x, mag_y, mag_z;

// dt
unsigned long t_now;
unsigned long t_prev;
float dt = 0.0;

// 오일러각
float accel_angle_x, accel_angle_y, accel_angle_z;
float gyro_angle_x, gyro_angle_y, gyro_angle_z;

// 상보필터로 구한 각 = 최종각
float filtered_angle_x, filtered_angle_y, filtered_angle_z;

// 제어 기준값
float init_angle_x, init_angle_y, init_angle_z;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  calibAccelGyro();
  initDT();
  //accelNoiseTest();
  initYPR();
}

void loop() {
  IMU.readAcceleration(accel_x, accel_y, accel_z);
  IMU.readGyroscope(gyro_x, gyro_y, gyro_z);
  IMU.readMagneticField(mag_x, mag_y, mag_z);
  calcDT();
  calcAccelYPR();
  calcGyroYPR();
  calcFilteredYPR();

  calcYPRtoDualPID();
  calcMotorSpeed();
  checkMspPacket();
  updateMotorSpeed();

  //static int cnt;
  //cnt++;
  //if(cnt%2 == 0) {
  //SendDataToProcessing();
}

extern float roll_output, pitch_output, yaw_output;
extern float motorA_speed, motorB_speed, motorC_speed, motorD_speed;

//void SendDataToProcessing() {
//Serial.print("DEL: ");
//Serial.print(dt, DEC);
//Serial.print("#RPY: ");
//Serial.print(filtered_angle_y, 2);
//Serial.print(",");
//Serial.print(filtered_angle_x, 2);
//Serial.print(",");
//Serial.print(filtered_angle_z, 2);
//Serial.print("#PID");
//Serial.print(roll_output, 2);
//Serial.print(",");
//Serial.print(pitch_output, 2);
//Serial.print(",");
//Serial.print(yaw_output, 2);
//Serial.print("#A");
//Serial.print(motorA_speed, 2);
//Serial.print("#B");
//Serial.print(motorB_speed, 2);
//Serial.print("#C");
//Serial.print(motorC_speed, 2);
//Serial.print("#D");
//Serial.print(motorD_speed, 2);
//}

int calibAccelGyro() {
  float sumAcX = 0, sumAcY = 0, sumAcZ = 0;
  float sumGyX = 0, sumGyY = 0, sumGyZ = 0;

  for (int i = 0; i < 10; i++) {
    IMU.readAcceleration(accel_x, accel_y, accel_z);
    IMU.readGyroscope(gyro_x, gyro_y, gyro_z);
    sumAcX += accel_x, sumAcY += accel_y, sumAcZ += accel_z;
    sumGyX += gyro_x, sumGyY += gyro_y, sumGyZ += gyro_z;
    delay(100);
  }

  baseAcX = sumAcX / 10;
  baseAcY = sumAcY / 10;
  baseAcZ = sumAcZ / 10;

  baseGyX = sumGyX / 10;
  baseGyY = sumGyY / 10;
  baseGyZ = sumGyZ / 10;
}

int initDT() {
  t_prev = micros();
}

int calcDT() {
  t_now = micros();
  dt = (t_now - t_prev) / 1000000.0;
  t_prev = t_now;
}

int calcAccelYPR() {
  float accel_x, accel_y, accel_z;
  float accel_xz, accel_yz;
  const float RADIANS_TO_DEGREES = 180 / 3.14159;

  accel_x = AcX - baseAcX;
  accel_y = AcY - baseAcY;
  accel_z = AcZ + (16384 - baseAcZ);

  accel_yz = sqrt(pow(accel_y, 2) + pow(accel_z, 2));
  accel_angle_y = atan(-accel_x / accel_yz) * RADIANS_TO_DEGREES;

  accel_xz = sqrt(pow(accel_x, 2) + pow(accel_z, 2));
  accel_angle_x = atan(accel_y / accel_xz) * RADIANS_TO_DEGREES;

  accel_angle_z = 0;
}

int calcGyroYPR() {
  const float GYROXYZ_TO_DEGREES_PER_SEC = 131;

  gyro_x = (GyX - baseGyX) / GYROXYZ_TO_DEGREES_PER_SEC;
  gyro_y = (GyY - baseGyY) / GYROXYZ_TO_DEGREES_PER_SEC;
  gyro_z = (GyZ - baseGyZ) / GYROXYZ_TO_DEGREES_PER_SEC;

  //gyro_angle_x += gyro_x = dt;
  //gyro_angle_y += gyro_y = dt;
  //gyro_angle_z += gyro_z = dt;
}

int calcFilteredYPR() {
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
}

//void accelNoiseTest() {
//analogWrite(6, 40);
//analogWrite(10, 40);
//analogWrite(9, 40);
//analogWrite(5, 40);
//}

//void stdPID(float& setpoint,
            //float& input,
            //float& prev_input,
            //float& kp,
            //float& ki,
            //float& kd,
            //float& iterm,
            //float& output) {
  //float error;
  //float dInput;
  //float pterm, dterm;

  //error = setpoint - input;
  //dInput = input - prev_input;
  //prev_input = input;

  //pterm = kp * error;
  //iterm += ki * error * dt;
  //dterm = -kd * dInput / dt;

  //output = pterm + iterm + dterm;
//}

//float roll_target_angle = 0.0;
//float roll_prev_angle = 0.0;
//float roll_kp = 0.408;
//float roll_ki = 1.02;
//float roll_kd = 0.0408;
//float roll_iterm;
//float roll_output;

//float pitch_target_angle = 0.0;
//float pitch_prev_angle = 0.0;
//float pitch_kp = 0.408;
//float pitch_ki = 1.02;
//float pitch_kd = 0.0408;
//float pitch_iterm;
//float pitch_output;

//float yaw_target_angle = 0.0;
//float yaw_prev_angle = 0.0;
//float yaw_kp = 1;
//float yaw_ki = 0;
//float yaw_kd = 0;
//float yaw_iterm;
//float yaw_output;

float base_roll_target_angle;
float base_pitch_target_angle;
float base_yaw_target_angle;

int initYPR() {
  for (int i = 0; i < 10; i++) {
    IMU.readAcceleration(accel_x, accel_y, accel_z);
    IMU.readGyroscope(gyro_x, gyro_y, gyro_z);
    IMU.readMagneticField(mag_x, mag_y, mag_z);
    calcDT();
    calcAccelYPR();
    calcGyroYPR();
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
}

//void calcYPRtoStdPID() {
//  stdPID(roll_target_angle,
         //filtered_angle_y,
         //roll_prev_angle,
         //roll_kp,
         //roll_ki,
         //roll_kd,
         //roll_iterm,
         //roll_output);

  //stdPID(pitch_target_angle,
         //filtered_angle_x,
         //pitch_prev_angle,
         //pitch_kp,
         //pitch_ki,
         //pitch_kd,
         //pitch_iterm,
         //pitch_output);

  //stdPID(yaw_target_angle,
         //filtered_angle_z,
         //yaw_prev_angle,
         //yaw_kp,
         //yaw_ki,
         //yaw_kd,
         //yaw_iterm,
         //yaw_output);
//}

float throttle = 100.0;
float motorA_speed, motorB_speed, motorC_speed, motorD_speed;

void calcMotorSpeed() {
  motorA_speed = (throttle == 0) ? 0:
    throttle + yaw_output + roll_output + pitch_output;
  motorB_speed = (throttle == 0) ? 0:
    throttle - yaw_output - roll_output + pitch_output;
  motorC_speed = (throttle == 0) ? 0:
    throttle + yaw_output - roll_output - pitch_output;
  motorD_speed = (throttle == 0) ? 0:
    throttle - yaw_output + roll_output - pitch_output;
  float throttle = 0;

  if (motorA_speed < 0) motorA_speed = 0;
  if (motorA_speed > 255) motorA_speed = 255;
  if (motorB_speed < 0) motorB_speed = 0;
  if (motorB_speed > 255) motorB_speed = 255;
  if (motorC_speed < 0) motorC_speed = 0;
  if (motorC_speed > 255) motorA_speed = 255;
  if (motorD_speed < 0) motorD_speed = 0;
  if (motorD_speed > 255) motorD_speed = 255;
}

enum {
  HEAD1, HEAD2, HEAD3, DATASIZE, CMD,
  ROLL, PITCH, YAW, THROTTLE,
  AUX, CRC, PACKETSIZE,
};
uint8_t mspPacket[PACKETSIZE];

void checkMspPacket() {
  static uint32_t cnt;

  if (Serial1.available() > 0) {
    while (Serial1.available() > 0) {
      uint8_t mspData = Serial1.read();
      if (mspData == '$') cnt = HEAD1;
      else cnt++;

      mspPacket[cnt] = mspData;

      if (cnt == CRC) {
        if (mspPacket[CMD] == 150) {
          throttle = mspPacket[THROTTLE];

          //float roll_ku = mspPacket[ROLL];
          //roll_ku -= 125;
          //if(roll_ku < 0) roll_ku = 0;
          //roll_ku /= 25;
          //roll_kp = roll_ku;
          //
          //Serial.print(throttle, 2);
          //Serial.print("\t");
          //Serial.println(roll_kp, 2);
        }
      }
    }
  }
}

#define THROTTLE_MAX 255
#define THROTTLE_MIN 0

int motorA_pin = 6;
int motorB_pin = 10;
int motorC_pin = 9;
int motorD_pin = 5;

void initMotorSpeed() {
  analogWrite(motorA_pin, THROTTLE_MIN);
  analogWrite(motorB_pin, THROTTLE_MIN);
  analogWrite(motorC_pin, THROTTLE_MIN);
  analogWrite(motorD_pin, THROTTLE_MIN);
}

void updateMotorSpeed() {
  analogWrite(motorA_pin, motorA_speed);
  analogWrite(motorB_pin, motorB_speed);
  analogWrite(motorC_pin, motorC_speed);
  analogWrite(motorD_pin, motorD_speed);
}

void dualPID(
   float target_angle,
   float angle_in,
   float rate_in, 
   float stabilize_kp, 
   float stabilize_ki, 
   float rate_kp, 
   float rate_ki, 
   float& stabilize_iterm, 
   float& rate_iterm, 
   float& output
   ) {
    float angle_error;
    float desired_rate;
    float rate_error;
    float stabilize_pterm, rate_pterm;

    angle_error = target_angle - angle_in;

    stabilize_pterm = stabilize_kp * angle_error;
    stabilize_iterm += stabilize_ki * angle_error * dt;

    desired_rate = stabilize_pterm;

    rate_error = deaired_rate - rate_in;

    rate_pterm = rate_kp * rate_error;
    rate_iterm += rate_ki * rate_error * dt;

    output = rate_pterm + rate_iterm + stabilize_iterm;    
   }
