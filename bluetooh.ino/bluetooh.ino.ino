int state = 0;

void setup() {
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  
  // put your setup code here, to run once:

}

void loop() {
  if(Serial.available() > 0)
  {
    state = Serial.read();
  }
  if (state == '0')
  {
    digitalWrite(13,LOW);
    Serial.println("off");
    state = 0;
  }
  else if (state == '1')
  {
    digitalWrite(13,HIGH);
    Serial.println("ON");// put your main code here, to run repeatedly:
  }
  delay(50); 

}
