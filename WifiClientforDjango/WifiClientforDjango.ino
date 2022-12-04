
#include <ESP8266WiFi.h>
//Wifi details
const char* ssid = "POCO X2";
const char* password = "Wifijoinkar";

//Server details
const char* host = "192.168.133.141";
const uint16_t port = 8000;




void setup() {
  Serial.begin(115200);//Serial start
  delay(10);
  WiFi.mode(WIFI_STA); //Wifi mode in STATION mode
  WiFi.begin(ssid, password);//Wifi begin

  //Wait for wifi connetion
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Connected");
  
  
}

void loop() {
  WiFiClient client; // TCP connection as a client
  if(client.connect(host, port))
 {
  
  Serial.println("[INFO] Server Connected - HTTP GET Started");   
    // Make HTTP GET request
  client.println("GET /about HTTP/1.1");
  client.println("Host: 192.168.133.141:8000");
  client.println("Connection: close");
  client.println();
  //Serial.println("[INFO] HTTP GET Completed");
 }
 delay(5000);
 
  while (client.available()) {
    char ch = static_cast<char>(client.read());
    Serial.print(ch);
    
  }
  Serial.println();
  Serial.print(".................End>>>>>>");
  //check if client is connected to the server

  //client is consuideere connecyeed is ther is unredd data and the connection is closed
 
}
/*Temperatur and Humidity from DHT11*/
/*
float  getHumidity(int analogChannel,  float temperature)
{
float supplyVolt =  5.0;
int DHT11_Value = analogRead(analogChannel);
float analogReading = DHT11_Value/1023.0 * supplyVolt;
float sensorReading = 161.0 * analogReading / supplyVolt - 25.8;
float humidityReading = sensorReading / (1.0546-0.0026*temperature);
return humidityReading;
}*/
