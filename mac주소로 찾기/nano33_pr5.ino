unsigned char temp[12] = {0,};
unsigned char rss[3] = {0,};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);
}

void loop() {

  // 수신받은 데이터가 없으면 블루투스 모듈에 데이터 요청
  if(Serial1.available())  {
       Serial1.write("AT+DISI?");
       delay(100); 
      
  }

  // 데이터가 다 떨어질 때 까지
    
     // F 찾기
    if(Serial1.available()) {
        Serial.print(Serial1.available()); 
        Serial.println("");
      if(Serial1.read() == 'F'){
      delay(10);
        Serial.print("buff :");
        Serial.print(Serial1.available()); 
        Serial.println("");
      if(Serial1.read() == 'C') {
        delay(10);
        Serial.print("buff :");
        Serial.print(Serial1.available()); 
        Serial.println("");
        if(Serial1.read() == '6') {
          delay(10);
          Serial.print("buff :");
          Serial.print(Serial1.available()); 
          Serial.println("");
          if(Serial1.read() == '9') {
            delay(10);
            Serial.print("buff :");
            Serial.print(Serial1.available()); 
            Serial.println("");
            if(Serial1.read() == '4') {
              Serial1.readBytes(temp,12);
              Serial.write(temp,12);
              Serial.print("buff :");
              Serial.print(Serial1.available()); 
              Serial.println("");
              
            }
          }
          
        }
      } 
    }
    
}
}
