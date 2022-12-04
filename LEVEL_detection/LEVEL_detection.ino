unsigned long start;
int count = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(6, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  

}

void loop() {
  int glow = digitalWrite(13, HIGH);
  // put your main code here, to run repeatedly:
  if(digitalRead(6) && count==0)
  {
    start = millis();
    count = 1;
    glow = !glow;
  }
  else if(!digitalRead(6)){
    count = 0;
  }
  
}
