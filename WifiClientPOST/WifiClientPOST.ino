#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#ifndef STASSID
#define STASSID "POCO X2"
#define PASS    "Wifijoinkar"
#endif
const char* ssid = STASSID;
const char* password = PASS;

const char* host = "192.168.35.141";
//const char* host = {"www.httpbin.org"};
const uint16_t port = 8000;
int temp = 10;
int hum = 9;
void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  
}


void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client;
  String User = "humidity="+String(temp);
  User += " "+String(hum);
 
  


  
  if(!client.connect(host, port))
  {
    Serial.println("Server not founnd");
    delay(5000);
    return;
  }
  Serial.println("Connection started ");
  if(client.connected())
  {
    Serial.println("Server Connected");
    client.println("POST /post HTTP/1.1");
    client.println("Host: "+String(host));
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Connection: keep-alive");
    client.print("Content-Length: ");
    client.println(User.length());
    client.println();
    client.println(User);
    Serial.println("data sent");
    
  }
  unsigned long timeout = millis();
  while(client.available() == 0)
  {
    if(millis()-timeout > 5000)
    {
      Serial.println("<<<<< Client timeout >>>>");
      client.stop();
      delay(60000);
      return;
    }
  }
  Serial.println("Reading data");
  while(client.available())
  {
    String dta = client.readStringUntil('\r');
    Serial.print(dta);
  }

  Serial.println();
  Serial.println("closig connection");
  client.stop();
  delay(3000);
  

}
