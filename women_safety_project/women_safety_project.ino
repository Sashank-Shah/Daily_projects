#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#include <TinyGPS++.h>
#include <SoftwareSerial.h>


#define REPORTING_PERIOD_MS     1000
#define PERIOD_MS               5000

static const int RXPin = 2, TXPin = 3;
static const uint32_t gps_baudrate = 9600;
TinyGPSPlus gps;
SoftwareSerial soft(RXPin, TXPin);



PulseOximeter pox;
uint32_t tsLastReport = 0;

float Lat, Lon;

String pulseAlert = "Pulse Alert ";
String soSAlert = "SoS Alert ";

volatile int BPM;
  
void onBeatDetected()
{
    ;
}

void soScall(String message)
{
    pox.update();
    digitalWrite(4,HIGH);
    pox.update();
    Serial.print("AT+CMGF=1\r");
    for(int i=0; i<50; i++)
    {
      delay(10);
      pox.update();
    }
    digitalWrite(4,LOW);
    Serial.println("AT+CMGS =\"+919337611772\"");
    for(int i=0; i<50; i++)
    {
      delay(10);
      pox.update();
    }
    
    pox.update();
    Serial.print(message);
    Serial.print(" Lat: ");
    Serial.print(Lat, 6);
    Serial.print(" Log: ");
    Serial.println(Lon, 6);
     pox.update();
    for(int i=0; i<50; i++)
    {
      delay(10);
      pox.update();
    }
    Serial.println((char)26);
    for(int i=0; i<10; i++)
    {
      delay(10);
      pox.update();
    }
    Serial.println();
    digitalWrite(4,LOW);
    pox.update();
    
}


void setup()
{
  soft.begin(gps_baudrate);
  Serial.begin(9600);
  pinMode(12,INPUT);
  pinMode(4, OUTPUT);

  if (!pox.begin()) {
        for(;;);
    }

    // pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
    pox.setOnBeatDetectedCallback(onBeatDetected);
    while(millis() <= PERIOD_MS)
     { // Serial.println(".");
      pox.update();
      pox.getHeartRate();
    }
}


void loop()
{
  int key = digitalRead(12);
  pox.update();
  
  while (soft.available() > 0)
  {
    gps.encode(soft.read());
    if (gps.location.isUpdated())
    {
      Lat = gps.location.lat();
      Lon = gps.location.lng();
      pox.update();
    }
    else;
  }
  pox.update();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS)
    {
      pox.update();
      BPM = pox.getHeartRate();
      
      if (BPM > 100)
      {
        soScall(pulseAlert);
      }
        
      tsLastReport = millis();
      pox.update();
    }
    
  if(key==0)
  {
    soScall(soSAlert);
    
  }
  pox.update();
  
}
