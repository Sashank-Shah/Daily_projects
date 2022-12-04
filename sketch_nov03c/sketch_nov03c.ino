
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
static const int RXPin = 2, TXPin = 3;
static const uint32_t gps_baudrate = 9600;
TinyGPSPlus gps;
SoftwareSerial soft(RXPin, TXPin);

float Lat, Lon;

void soScall()
{
    Serial.print("AT+CMGF=1\r");
    delay(500);
    digitalWrite(4,LOW);
    Serial.println("AT+CMGS =\"+917788942694\"");
    delay(500);
    Serial.println("Sos pressed " + String("Lat: ") +String(Lat) + " "+String("Lon: ") + String(Lon));
    delay(500);
    Serial.println((char)26);
    delay(100);
    Serial.println();
    
}


void setup()
{
  soft.begin(gps_baudrate);
  Serial.begin(9600);
  pinMode(12,INPUT);
  pinMode(4, OUTPUT);
}
void loop()
{
  int key = digitalRead(12);
  while (soft.available() > 0)
  {
    gps.encode(soft.read());
    if (gps.location.isUpdated())
    {
      Lat = gps.location.lat();
      Lon = gps.location.lng();
    }
    else;
  }
  if(key==0)
  {
    digitalWrite(4,HIGH);
    soScall();
    digitalWrite(4,LOW);
  }
  
}
