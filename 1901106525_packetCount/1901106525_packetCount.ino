
unsigned int count=0;
unsigned int state=1;
void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
}

void dsplay(){
  if (state==1){
    count++;
    Serial.println("No. of packets:");
    Serial.println(count);
  }
  state=0;
  
}

void loop() {
  int sensorValue = digitalRead(2);
  while(sensorValue==0){};
  if (sensorValue==1){
    state=1;
    dsplay();
  }
  delay(1);
 }
