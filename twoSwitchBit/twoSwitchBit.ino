void setup() {
  pinMode(2,INPUT);
  pinMode(3,INPUT);// put your setup code here, to run once:
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);

}

void loop() {
  if(digitalRead(2)){
    digitalWrite(13,LOW);
  }
  else if(digitalRead(3)){
    digitalWrite(13,HIGH);
  }
  else{
    digitalWrite(12,HIGH);
  }
}
