#include <BluebeeFC.h>

#define THROTTLE_MAX 255
#define THROTTLE_MIN 0
#define MAX_CONTROL_ANGLE 10

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

// 현재 드론 각도
PostureAngle angle = {0.0, };

// dt
unsigned long t_now;
unsigned long t_prev;
float dt = 0.0;


// 초기각도 값 
float base_roll_target_angle = 0;
float base_pitch_target_angle = 0;
float base_yaw_target_angle = 0;

float throttle = 0.0;
float motorA_speed;
float motorB_speed; 
float motorC_speed;
float motorD_speed;


/* 비콘 디텍터 관련 변수들  */
// 멈춰 비콘 감지 변수
int isStopBeaconDetected = 0;
// 조종기 명령 제어 변수
int ignoreController = 0;

rtos::Thread thread;

void setup() {

  // 제어기 게인값 설정
  cv_roll.stabilize_kp = 1;
  cv_roll.rate_kp = 0.8;
  cv_roll.rate_ki = 0.0;
  cv_roll.rate_kd = 0.0;
  cv_pitch.stabilize_kp = 1;
  cv_pitch.rate_kp = 0.8;
  cv_pitch.rate_ki = 0.0;
  cv_pitch.rate_kd = 0.0;
  cv_yaw.stabilize_kp = 0;
  cv_yaw.rate_kp = 0.8;
  cv_yaw.rate_ki = 0.0;
  cv_yaw.rate_kd = 0.0;


  Serial.begin(115200);
  Serial1.begin(9600);
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
     while (1);
  }

  calibAccelGyro();
  initDT();
  initYPR();

  thread.start(FlightControl);
  thread.set_priority(osPriorityRealtime);
}

void loop() {}

void FlightControl()  {
  // 비행제어기 작동 알림 LED
  digitalWrite(LED_GREEN, HIGH);

  while(1)  {
    IMU.readAcceleration(sdata.accel_x, sdata.accel_y, sdata.accel_z);
    IMU.readGyroscope(sdata.gyro_x, sdata.gyro_y, sdata.gyro_z);
    calcDT();
    calcFilteredYPR(
      &sdata,
      &angle,
      &dt
    );
    calcYPRtoDualPID(
      &cv_roll,
      &cv_pitch,
      &cv_yaw,
      &sdata,
      &angle,
      &dt
    );
    calcMotorSpeed();

    // beacon_thread 에 의해 ignoreController 가 false -> true 로 바뀜
    if(!ignoreController) {
      checkMspPacket();
    }

    // ignoreController 가 true 일때 
    // 조종기 무시, throttle = 0
    else  {
      throttle = 0;
    }

    updateMotorSpeed(
    &motorA_speed,
    &motorB_speed,
    &motorC_speed,
    &motorD_speed
    );
    // FlightData 구조체 데이터 초기화
    fdata.dt = dt;
    fdata.filtered_angle_x = angle.roll;
    fdata.filtered_angle_y = angle.pitch;
    fdata.filtered_angle_z = angle.yaw;
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


int initYPR() {


  for (int i = 0; i < 1000; i++) {
    IMU.readAcceleration(sdata.accel_x, sdata.accel_y, sdata.accel_z);
    IMU.readGyroscope(sdata.gyro_x, sdata.gyro_y, sdata.gyro_z);

    calcDT();
    calcFilteredYPR(
    &sdata,
    &angle,
    &dt
  );

    base_roll_target_angle += angle.pitch;
    base_pitch_target_angle += angle.roll;
    base_yaw_target_angle += angle.yaw;

  }

  base_roll_target_angle /= 1000;
  base_pitch_target_angle /= 1000;
  base_yaw_target_angle /= 1000;

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

          cv_roll.target -= (float)(mspPacket[5] - 125) * MAX_CONTROL_ANGLE/125;
          cv_pitch.target += (float)(mspPacket[6] - 125) * MAX_CONTROL_ANGLE/125;
          cv_yaw.target -= (float)(mspPacket[7] - 125) * MAX_CONTROL_ANGLE/125;
          
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

/* 비콘 감지 함수 */
/* 이 부분은 void setup() 의 BLE.begin() 때문에 소스코드 분리 안함
*/
int BeaconDetector()  {

    char MAC[18] = "18:93:d7:2a:8e:a4";
    
  // check if a peripheral has been discovered
    if(!BLE.available()) { 
      BLE.scanForAddress(MAC);
    }

    BLEDevice peripheral = BLE.available();

    if (peripheral) {
      if (peripheral.rssi() > -61)  return 1;
    }
    return 0;
}
