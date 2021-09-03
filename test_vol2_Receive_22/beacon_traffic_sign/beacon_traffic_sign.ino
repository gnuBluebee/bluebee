#include <ArduinoBLE.h>
char MAC[18] = "18:93:d7:2a:8e:a4";

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");

    while (1);
  }

  // start scanning for peripheral
  BLE.scan();
  
}

void loop() {
  int isStopBeaconDetected = 0;

  delay(5);
  isStopBeaconDetected = BeaconDetector();
  if(isStopBeaconDetected)  Serial.println("STOP");
  
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
