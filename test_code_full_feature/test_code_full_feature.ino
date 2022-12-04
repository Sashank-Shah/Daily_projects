#include <TinyGPS++.h>
#include <Wire.h>    
#include <MAX30100_PulseOximeter.h>  
#include <SoftwareSerial.h>

#define REPORTING_PERIOD_MS     1000
PulseOximeter pox;
uint32_t tsLastReport = 0;
volatile float BPM;

static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
volatile float latitude;
volatile float longitude;

static const int RXPin = 5, TXPin = 6;
SoftwareSerial ss(RXPin, TXPin);
const int button = 3;


void onBeatDetected()
{
    ;
}

void SendMessage(float latitude, float longitude)
{
  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r"); // Replace x with mobile number
  delay(1000);
  Serial.println("Lat: "+String(latitude)+" lng: "+String(longitude));// The SMS text you want to send
  delay(100);
   Serial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void SendAlert()
{
  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r"); // Replace x with mobile number
  delay(500);
  Serial.println("Pulse Alert !");// The SMS text you want to send
  delay(100);
   Serial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void SendHelp()
{
  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r"); // Replace x with mobile number
  delay(500);
  Serial.println("SOS button pressed");// The SMS text you want to send
  delay(100);
   Serial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void setup() {
  Serial.begin(GPSBaud);  //for gsm modoule
  ss.begin(GPSBaud);  //for gps module
  pinMode(5, OUTPUT);
  pinMode(button, INPUT);
  
  if (!pox.begin()) {
        for(;;);
    }
   
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  pox.setOnBeatDetectedCallback(onBeatDetected);
 
}

void loop() {
        pox.update();
        BPM = pox.getHeartRate();
        digitalWrite(5, LOW);
        if ((BPM > 100) || (BPM < 50))
        {
          digitalWrite(5, HIGH);
          SendAlert();
          while (ss.available())
          {
            if(gps.encode(ss.read()))
            {
              if(gps.location.isValid())
              {
                latitude = gps.location.lat();
                longitude = gps.location.lng();
                SendMessage(latitude, longitude);
                delay(100);
                break;
              }
            }
            delay(500);
            
            }
         }

         else if(digitalRead(button) == HIGH)
         {
            SendHelp();
            while (ss.available())
          {
            if(gps.encode(ss.read()))
            {
              if(gps.location.isValid())
              {
                latitude = gps.location.lat();
                longitude = gps.location.lng();
                SendMessage(latitude, longitude);
                delay(100);
                break;
              }
            }
            delay(500);
            
            }
         }
          
          
}
