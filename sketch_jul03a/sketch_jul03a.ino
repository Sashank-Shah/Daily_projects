#include <ESP8266WiFi.h>

const char* ssid="POCO X2";
const char* password="Wifijoinkar";
IPAddress staticIP(192,111,1,11);
IPAddress gateway(192,168,53,57);
IPAddress subnet(225,225,225,0);


void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.print(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.config(staticIP,gateway,subnet);
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Wifi Connected");
  Serial.println(WiFi.localIP());
  Serial.println("Gateway IP");
  Serial.println(WiFi.gatewayIP());
  Serial.println("Subnet");
  Serial.println(WiFi.subnetMask());
  Serial.println("Mac Address");
  Serial.println(WiFi.macAddress());
  Serial.println("SSID");
  Serial.println(WiFi.SSID());
  Serial.println("Passsword");
  Serial.println(WiFi.psk());
  Serial.println("Strength");
  Serial.print(WiFi.RSSI());
  
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
