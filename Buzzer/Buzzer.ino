int buzzer1 = 12;
int buzzer2 = 7;
int ir = 8;
int irtest = 0;

void setup()
{
  pinMode(buzzer1,OUTPUT);
  pinMode(buzzer2,OUTPUT);
  pinMode(ir,INPUT);
  
}

void loop()
{
  irtest=digitalRead(ir);
  if(irtest == 1)
  {
    digitalWrite(buzzer1,HIGH);
  }
  else
  {
    digitalWrite(buzzer2,HIGH);
  }
}
  
