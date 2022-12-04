#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 4, TXPin = 5;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);
volatile float lati, longi;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ss.begin(GPSBaud);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (ss.available())
  {
    if(gps.encode(ss.read()))
    {
      if(gps.location.isUpdated())
      {
            lati = gps.location.lat();
            longi = gps.location.lng();
      }
    }
    Serial.println(lati);
  Serial.println(longi);
    delay(1000);
  }
  Serial.println(lati);
  Serial.println(longi);
  Serial.println(".");
  delay(1000);
}
