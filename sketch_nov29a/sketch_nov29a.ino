#define RLOAD 22.0
#include <MQ135.h>
MQ135 gasSensor = MQ135(A1);
int val;
int sensorPin = A1;
int sensorValue = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Started ");
  pinMode(sensorPin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
val = analogRead(A1);
Serial.print ("raw = ");
Serial.println (val);
float ppm = gasSensor.getPPM();
Serial.print ("ppm: ");
Serial.println (ppm);
delay(1000);
}
