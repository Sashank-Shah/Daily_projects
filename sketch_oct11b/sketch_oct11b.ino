
//#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <WiFiClient.h>
#define httpPort 80

static const int RXPin = D6, TXPin = ;

static const uint32_t GPSBaud = 9600;


const char* ssid = "POCO X2";
const char* password = "Wifijoinkar";


String apiKey = "2Z8Y3RBSKWN3F35C";

const char* server = "api.thingspeak.com";

// The TinyGPS++ object
TinyGPSPlus gps;
SoftwareSerial Ss(RXPin, TXPin);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Ss.begin(GPSBaud);
 
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wifi connected");

  delay(100);

}

void loop() {
  // put your main code here, to run repeatedly:
  while (Ss.available() > 0)
  {
    float speedv;
    
    
    if(gps.encode(Ss.read()))
    {
      if(gps.location.isValid())
      {
        speedv = gps.speed.mps();
        
        }
    }
        
    WiFiClient client;

    HTTPClient http;
    if (!client.connect(server,  httpPort))
    {
      Serial.println("connection failed");
    }
   
    //String url = "/speeddett/insert.php?temp=" + String(speedv); 
    String url = "/update?api_key=2Z8Y3RBSKWN3F35C&field1="+String(speedv);
    
    /*Serial.print("Requesting URL: ");
    Serial.println(url);
 */
    
  //url = url + (String)speedValue;

    http.begin(server,httpPort,url); 
    int httpCode = http.GET();
   
    Serial.println(speedv);
    
    delay(100);
  

  }
  
  
  delay(2000);

}
