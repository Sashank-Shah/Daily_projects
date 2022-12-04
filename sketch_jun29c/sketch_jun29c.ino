volatile boolean st = false;
volatile int count = 0;
void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  attachInterrupt(0,itsON,RISING);
  attachInterrupt(1,itsOFF,FALLING);
}

void loop() {
  if(st==true)
  {
    Serial.begin(9600);
    delay(5);
    count++;
    Serial.println("No. of packets:");
    Serial.println(count);
  }
  st=false;

}

void itsON()
{
  st=true;
}

void itsOFF()
{
  st=false;
}
