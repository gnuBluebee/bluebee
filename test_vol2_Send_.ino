//int sig = 5;
//byte count = 1;
//
//void setup() {
//  pinMode(sig, OUTPUT);
//}
//
//void loop() {
//  
//  if(count % 2 == 0) {
//    digitalWrite(sig, HIGH);
//    count = count + 1;
//    delay(500);
//  }
//  else {
//    digitalWrite(sig, LOW);
//    count = count + 1;
//    delay(1000);
//  }
//}

#include <ArduinoBLE.h>
char MAC[18] = "18:93:d7:2a:8e:a4";
int isStopBeaconDetected = 0;
const int sig = 11;

void setup() {
  // BLE 모듈 시작
  if(!BLE.begin()) while(1);

  
  pinMode(sig, OUTPUT);
}

int BeaconDetector()  {
  // check if a peripheral has been discovered
  if(!BLE.available())
    BLE.scan();
    
  BLEDevice peripheral = BLE.available();

  if (peripheral) {

    // print address
   
    if (String(peripheral.address()) == MAC) {
      if (peripheral.rssi() > -61)  return 1;
    }
  }

  return 0;
}

void loop() {
  isStopBeaconDetected = BeaconDetector();
  if(isStopBeaconDetected == 1) {
    digitalWrite(sig, HIGH);
  }
  else {
    digitalWrite(sig, LOW);
  }
}
