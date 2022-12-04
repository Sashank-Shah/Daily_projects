#define RLOAD 18.0
#include <MQ135.h>

float rzero = 0.0;
MQ135 gasSensor = MQ135(A0);
void setup (){
Serial.begin (9600);
pinMode(A0, INPUT);
}
void loop() {
for(int i=0; i<500; i++)
{
   // Attach sensor to pin A0
  rzero = rzero + gasSensor.getRZero();
}
rzero = rzero/500;

Serial.println (rzero);
float ppm = gasSensor.getPPM();
Serial.println(ppm);
delay(1000);
}
