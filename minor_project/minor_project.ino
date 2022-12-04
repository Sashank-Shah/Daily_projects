#include <ESP8266WiFi.h>

#define RLOAD 22.0
#include <MQ135.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

String apiKey = "6O07RAHO4KV5BYRM";
const char* ssid = "POCO X2";
const char* password = "Wifijoinkar";
const char* server = "api.thingspeak.com";


static const int RXPin = D1, TXPin = D0;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;      // The TinyGPS++ object
SoftwareSerial ss(RXPin, TXPin);  // The serial connection to the GPS device


const int selectPins[4] = {D8, D7, D6, D5};
int analogInput = A0;

volatile int speedv;
volatile int val, latitude, longitude;


volatile float ppmCO2, ppmCO, ppmH2;
float RS_gas = 0;
float ratio = 0;
float sensorValue = 0;
float sensor_volt = 0;
float R0 = 7200.0;
 


float measureCO(volatile float val)
{
   sensor_volt = val/1024*4.0;
   RS_gas = (4.0-sensor_volt)/sensor_volt;
   ratio = RS_gas/R0; //Replace R0 with the value found using the sketch above
   float x = 1538.46 * ratio;
   return pow(x,-1.709);

}

float measureH2(volatile float val)
{
  
}

void setup() {
 
  Serial.begin(9600);
  ss.begin(GPSBaud);
  pinMode(analogInput, INPUT);
  for(int i=0; i<4; i++)
  {
    pinMode(selectPins[i], OUTPUT);
    digitalWrite(selectPins[i], HIGH);   //writing MSB bit first
  }
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  

}



void loop() {

  // put your main code here, to run repeatedly:
    Serial.println("Hold on Calibrating ....");
   
   if(ss.available())
   {
      
      if(gps.encode(ss.read()))
      {
      if (gps.location.isValid())
      { 
        //speedv = gps.speed.kmph();
        speedv = gps.speed.mps();//speed reading
        latitude = gps.location.lat();
        longitude = gps.location.lng();
      }
      /********Sensors********************/
       for (byte pin=0; pin <= 2; pin++)
      {
        for (int i=0; i < 4; i++)
        {
          digitalWrite(selectPins[i], pin & (1 << i)?HIGH:LOW);
        }
        if(pin == 0) //mq 135 =co2
        {
          MQ135 gasSensor = MQ135(analogInput);
          val = analogRead(analogInput);
          ppmCO2 = gasSensor.getPPM(); // co2 ppm value we needed
        }
        else if(pin == 1) //MQ 8 
        {
          val = analogRead(analogInput);
          ppmH2 = measureH2(val);
          
        }
        else if(pin == 3) // MQ 7 (CO)
        {
          val = analogRead(analogInput);
          ppmCO = measureCO(val);
               
        }
      }
      /********************sensors******************************/
     WiFiClient client;
     if (client.connect(server,80))
     {
        String postStr = apiKey;
        postStr +="&field1=";
        postStr += String(speedv);
        postStr +="&field2=";
        postStr += String(latitude);
        postStr +="&field3=";
        postStr += String(longitude);
        postStr +="&field4=";
        postStr += String(ppmCO2);
        postStr +="&field5=";
        postStr += String(ppmCO);
        postStr +="&field6=";
        postStr += String(ppmH2);
        postStr += "\r\n\r\n";
        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: keep-alive\n");
        client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(postStr.length());
        client.print("\n\n");
        client.print(postStr); 
     }
     client.stop(); 
     delay(2000);
  
   }
   
   }
    
   
}
