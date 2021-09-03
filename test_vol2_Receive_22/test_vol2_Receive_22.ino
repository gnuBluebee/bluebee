int led = 13;
int sig = 11;
int res = 0;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(sig, INPUT);
}

void loop() {
  res = digitalRead(sig);
  if(res == 1) {
    
  }
  
  digitalWrite(led, res);
}
