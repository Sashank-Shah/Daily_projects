#include <DHT.h>
#define dht_pin A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);
  Serial.println("DHT temperature and humidity Sensor");
  delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
  DHT.read11(dht_pin);
  Serial.print("humidity = ");
  Serial.print(DHT.humidity);
  Serial.print("Temperature = ");
  Serial.print(DHT.temperature);
  delay(2000);
  
  

}
