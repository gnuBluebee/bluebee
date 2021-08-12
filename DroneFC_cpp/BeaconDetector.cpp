#include <ArduinoBLE.h>

int BeaconDetector()  {
    char MAC[18] = "18:93:d7:2a:8e:a4";
    
    if (!BLE.begin()) {
        Serial.println("starting BLE failed!");
        while (1);
    }
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