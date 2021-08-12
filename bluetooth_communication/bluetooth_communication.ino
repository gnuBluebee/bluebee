void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
}

uint8_t mspPacket[11];

void loop() {
  static uint32_t cnt;

  if(Serial1.available() > 0) {
    while(Serial1.available() > 0) {
      uint8_t mspData = Serial1.read();
      if(mspData == '$') cnt = 0;
      else cnt++;

      mspPacket[cnt] = mspData;

      if(cnt == 10) printMspPacket();
    }
  }
}

void printMspPacket() {
  Serial.print((char)mspPacket[0]);
  Serial.print((char)mspPacket[1]);
  Serial.print((char)mspPacket[2]);
  Serial.print(mspPacket[3]);
  Serial.print(' ');
  Serial.print(mspPacket[4]);
  Serial.print('\t');
  Serial.print("R:");
  Serial.print(mspPacket[5]);
  Serial.print('\t');
  Serial.print("P:");
  Serial.print(mspPacket[6]);
  Serial.print('\t');
  Serial.print("Y:");
  Serial.print(mspPacket[7]);
  Serial.print('\t');
  Serial.print("T:");
  Serial.print(mspPacket[8]);
  Serial.print('\t');
  Serial.print(mspPacket[9]);
  Serial.print(' ');
  Serial.print(mspPacket[10]);
  Serial.print('\n');
}
