#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


int httpPort = 80;


//String url1 = "/update?api_key=2Z8Y3RBSKWN3F35C&field1=";

//String host = "spectrumcet.com/speeddett/insert.php";
String host = "http://18.217.222.254:80/speeddett/insert.php";
//String host = "api.thingspeak.com";



const char* ssid     = "POCO X2";
const char* password = "Wifijoinkar";

static const int RXPin = D8, TXPin = D0;

static const uint32_t GPSBaud = 9600;
// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);


void setup() {
  // put your setup code here, to run once:

   // Debug console
  Serial.begin(9600);
  ss.begin(GPSBaud);
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}


int speedv;

void loop() {

  // put your main code here, to run repeatedly:
    //Serial.println("GPS NOT FOUND!!!!!!!!!!");
    while(ss.available())
    {
      if(gps.encode(ss.read()))
      {
        if (gps.location.isUpdated())
        {
          speedv = gps.speed.kmph();
        }
      
      WiFiClient client;
      HTTPClient http;
      //const int httpPort = 80;
      /*if (!client.connect(host, httpPort))
      {
        Serial.println("connection failed");
        return;
      }*/
      //String url = "/update?api_key=2Z8Y3RBSKWN3F35C&field1="+String(speedv);
      String url = host + "?temp=" + String(speedv);
      Serial.println(url);
      
      http.begin(client, url);
      int httpCode = http.GET();
      Serial.println(httpCode);
      http.end();
      delay(1500);
      
   }
    }

 


 
  
   
}
