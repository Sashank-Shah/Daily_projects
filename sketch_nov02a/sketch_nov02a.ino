#include <ESP8266WiFi.h>

const char* ssid = "POCO X2";
const char* password = "Wifijoinkar";

const char* host = "http://www.httpbin.org";
const int port = 80;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  Serial.println("Connecting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client;
  String tex = "textdata=test";
  if(!client.connect(host, port))
  {
    delay(500);
    return;
  }
    Serial.println("Connected to server");
    if(client.connected())
    {
      Serial.println("inside");
      client.println("GET /get?"+tex+" HTTP/1.1");
      client.println("Host: "+String(host));
      client.println("Connection: close");
      client.println();
    }   
  
  while(client.available())
  {
    char c = client.read();
    Serial.write(c);
  }
  
  Serial.println();
  if (!client.connected())
  {
    Serial.println();
    Serial.println("[INFO] Disconnecting From Server");
    client.stop();  
  }
  delay(3000);
}
