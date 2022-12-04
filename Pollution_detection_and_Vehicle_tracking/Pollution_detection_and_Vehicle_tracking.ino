#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define RLOAD 18.0
#include <MQ135.h>

#define S0 D0                             /* Assign Multiplexer pin S0 connect to pin D0 of NodeMCU */
#define S1 D1                             /* Assign Multiplexer pin S1 connect to pin D1 of NodeMCU */
#define S2 D2                             /* Assign Multiplexer pin S2 connect to pin D2 of NodeMCU */
#define S3 D3                             /* Assign Multiplexer pin S3 connect to pin D3 of NodeMCU */
#define SIG A0                            /* Assign SIG pin as Analog output for all 16 channels of Multiplexer to pin A0 of NodeMCU */

/*Wifi config*/
String apiKey = "6O07RAHO4KV5BYRM";
const char* ssid = "POCO X2";
const char* password = "Wifijoinkar";
const char* server = "api.thingspeak.com";

/* GPS config */
static const int RXPin = D8, TXPin = D6;
static const uint32_t gps_baudrate = 9600;
TinyGPSPlus gps;
SoftwareSerial soft(RXPin, TXPin);
float Lat, Lon, speedv;


float ppmCOO, ppmCO, ppmHH; //sensor readings

//CO sensor values MQ-7

float m = -0.6527; //Slope 
float b = 1.30; //Y-Intercept 
float R0 = 0.71; //Sensor Resistance in fresh air from previous code

String Lati, Longi;


int sensor1;                            /* Assign the name "sensor1" as analog output value from Channel C1 */


void getCoValue()
{
  float sensor_volt; //Define variable for sensor voltage 
  float RS_gas; //Define variable for sensor resistance  
  float ratio; //Define variable for ratio
  int sensorValue = analogRead(SIG); //Read analog values of sensor  

  sensor_volt = sensorValue*(4.0/1023.0); //Convert analog values to voltage 
  RS_gas = ((4.0*10.0)/sensor_volt)-10.0; //Get value of RS in a gas
  ratio = RS_gas/R0;  // Get ratio RS_gas/RS_air
  double ppm_log = (log10(ratio)-b)/m; //Get ppm value in linear scale according to the the ratio value  
  ppmCO = pow(10, ppm_log); //Convert ppm value to log scale
}
MQ135 gasSensor = MQ135(SIG);
void getCOO()
{
  MQ135 gasSensor = MQ135(SIG);
  delay(500);
  ppmCOO = gasSensor.getPPM(); // co2 ppm value we needed
}


void setup() {
  // put your setup code here, to run once:
   pinMode(S0,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin SO */        
   pinMode(S1,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S1 */  
   pinMode(S2,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S2 */ 
   pinMode(S3,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S3 */  
   pinMode(SIG, INPUT);                      /* Define analog signal pin as input or receiver from the Multiplexer pin SIG */  
   Serial.begin(9600);                       /* to display readings in Serial Monitor at 9600 baud rates */
   soft.begin(gps_baudrate);
   WiFi.begin(ssid, password); 
   
   while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }
}

void loop() {
     while (soft.available() > 0)
    {
      gps.encode(soft.read());
      if (gps.location.isValid())
      {
        Lat = gps.location.lat();
        Lon = gps.location.lng();
        speedv = gps.speed.mps();
      }
      else;
    }
    //channel 11  (C0 pin - binary output  1,0,1,1)
    digitalWrite(S0,HIGH); digitalWrite(S1,HIGH); digitalWrite(S2,LOW); digitalWrite(S3,HIGH);
    getCOO();
    if(Lat <= 0)
    {
      Lat = 20.268780;
      Lon = 85.760660;
    }
    Serial.print("CO2: ");
    Serial.print(ppmCOO);
    Serial.println(" ppm");
    
    Serial.print("Lat: ");
    Serial.println(Lat, 6);
    Serial.print("Lon: ");
    Serial.println(Lon, 6);
    Serial.print("speed: ");
    Serial.println(speedv);
    
    // Channel 4 (C2 pin - binary output 0,1,0,0)
    digitalWrite(S0, LOW); digitalWrite(S1,LOW); digitalWrite(S2,HIGH); digitalWrite(S3,LOW);
    //sensor2 = analogRead(SIG);
    getCoValue();
    Serial.print("CO: ");
    Serial.print(ppmCO);
    Serial.println(" ppm");
    
    /*float rzero = gasSensor.getRZero();
    Serial.println(" rzero "); 
    Serial.println (rzero);*/
     Lati = String(Lat, 6);
     Longi = String(Lon, 6);
     WiFiClient client;
     if (client.connect(server,80))
     {
        String postStr = apiKey;
        postStr +="&field1=";
        postStr += String(ppmCOO);
        postStr +="&field2=";
        postStr += String(ppmCO);
        postStr +="&field3=";
        postStr += Lati;
        postStr +="&field4=";
        postStr += Longi;
        postStr +="&field5=";
        postStr += String(speedv);
        postStr += "\r\n\r\n";
        client.print("GET /update HTTP/1.1\n");
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
     delay(100);

   
}
