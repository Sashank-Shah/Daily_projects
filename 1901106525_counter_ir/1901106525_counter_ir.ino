volatile boolean st = false;
volatile int count = 0;
void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  attachInterrupt(0,itsON,RISING);
  attachInterrupt(1,itsOFF,FALLING);
}

void loop() {
  if(st==true)
  {
    Serial.println("No. of packets:");
    Serial.println(count);
  }
  st=false;

}

void itsON()
{
  st=true;
  count=count+1;
}

void itsOFF()
{
  st=false;
}
