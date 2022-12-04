#include <AFMotor.h>
const int out=12;
const int in=13;
AF_DCMotor motor1(1);
AF_DCMotor motor4(4);
char bt='S';

void setup()
{
  Serial.begin(9600);
  pinMode(in, INPUT);
  pinMode(out, OUTPUT);
  motor1.setSpeed(225);
  motor4.setSpeed(225);
  Stop();
}
long microsecondsToCentimeters(long microseconds)
{
return microseconds/29/2;
}

void loop() {
bt=Serial.read();

if(bt=='F')
{
 forward(); 
}

if(bt=='f')
{
 forward(); 
}

if(bt=='B')
{
 backward(); 
}

if(bt=='b')
{
 backward(); 
}

if(bt=='L')
{
 left(); 
}

if(bt=='l')
{
 left(); 
}

if(bt=='R')
{
 right(); 
}

if(bt=='r')
{
 right(); 
}

if(bt=='S')
{
 Stop(); 
}

if(bt=='s')
{
 Stop(); 
}
long dur;
long dis;
long tocm;
digitalWrite(out,LOW);
delayMicroseconds(2);
digitalWrite(out,HIGH);
delayMicroseconds(10);
digitalWrite(out,LOW);
dur=pulseIn(in,HIGH);
tocm=microsecondsToCentimeters(dur);
Serial.println(String(tocm));
delay(100);

if (tocm <= 12) {
   Stop();
}
}

void forward()
{
  motor1.run(FORWARD);
  motor4.run(FORWARD);
}

void backward()
{
  motor1.run(BACKWARD);
  motor4.run(BACKWARD);
}
void left()
{
  motor1.run(BACKWARD);
  motor4.run(FORWARD);
}
void right()
{
  motor1.run(FORWARD);
  motor4.run(BACKWARD);
}
void Stop()
{
  motor1.run(RELEASE);
  motor4.run(RELEASE);
}
