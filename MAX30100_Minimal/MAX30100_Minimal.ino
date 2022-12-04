

int button;


bool alert = false;

void onBeatDetected()
{
    ;
}

void pulseAlert()
{
  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("AT+CMGS=\"+919337611772\"\r"); // Replace x with mobile number
  delay(500);
  Serial.println("Pulse Alert !");// The SMS text you want to send
  delay(100);
   Serial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void setup()
{
    pinMode(4, INPUT);
    pinMode(12, OUTPUT);
    Serial.begin(9600);
    ss.begin(GPSBaud);
    
    if (!pox.begin()) {
        for(;;);
    }

    // pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
    pox.setOnBeatDetectedCallback(onBeatDetected);
    
    while(millis() <= PERIOD_MS)
    { // Serial.println(".");
      pox.update();
      pox.getHeartRate();
    }
}

void loop()
{
  
    pox.update();
    int button = digitalRead(4);
   /* while (ss.available())
      {
        if(gps.encode(ss.read()))
        {
          if(gps.location.isUpdated())
          {
            latitude = gps.location.lat();
            longitude = gps.location.lng();
         
          }
         }
        }*/
   
    alert = false;
    if (millis() - tsLastReport > REPORTING_PERIOD_MS)
    {
      if (pox.getHeartRate() > 98)
        alert = true;
        
      tsLastReport = millis();
      pox.update();
    }
    

    if (alert == true)
    {
      digitalWrite(12, HIGH);
      pulseAlert();
    }

 
    if (button == 0)
    {
      digitalWrite(12, HIGH);
      Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
      delay(1000);  // Delay of 1000 milli seconds or 1 second
      Serial.println("AT+CMGS=\"+919337611772\"\r"); // Replace x with mobile number
      delay(500);
      Serial.println("LAT: "+String(latitude));// The SMS text you want to send
      delay(100);
      Serial.println((char)26);// ASCII code of CTRL+Z
      delay(1000);
      digitalWrite(12, LOW);
      

    }
    

    
    
    
    
    
}
