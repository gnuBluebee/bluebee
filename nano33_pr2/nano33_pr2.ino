#define INDEX_LENGTH 78

unsigned char buff[78];
unsigned char indexchar[8];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(9600); 

}

void loop() {
  // put your main code here, to run repeatedly:
  if(!Serial1.available())
    Serial1.write("AT+DISI?");
    delay(1000);

   if(Serial1.available())  {
    Serial1.readBytes(indexchar,8);
      if(indexchar[0] == 'O'&& indexchar[6] == 'C') {

        while(Serial1.available()) {
           Serial1.readBytes(buff,78);
           
           for(int i=0; i<70; i++)  {
            Serial.write(buff[i]);
           }
           Serial.println("");

           delay(300);
           
        }
      }
      
        
      else  {
        Serial.println("BUG");
        Serial1.flush();
        
      }
   }   

}