#define DEBUG true
#include <SoftwareSerial.h>

static const int RXPin = 10, TXPin = 11;

static const uint32_t ESPBaud = 9600;

SoftwareSerial ss(RXPin, TXPin);

String Host="SSID";
String Password="Password";

String CHK="";

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  ss.begin(ESPBaud);
  
   char inv='"';
   String add="AT+CWJAP";
        add+="=";
        add+=inv;
        add+=Host;
        add+=inv;
        add+=",";
        add+=inv;
        add+=Password;
        add+=inv;
        add+="\r\n";
 CHK=sendData(add,5000,0);
     
}

void loop() {
  delay(2000);
int i=0;
  char inv='"';
   String add="AT+PING"; 
        add+="=";
        add+=inv;
        add+="www.google.com";
        add+=inv;
        add+="\r\n";
 CHK=sendData(add,2000,0);  // AT+PING="www.google.com"

Serial.println(CHK);

while(CHK.charAt(i)!='+')
i++;
i++;
CHK=CHK.substring(i);
i=0;
 while(CHK.charAt(i)!='+')
i++;
i++;
CHK=CHK.substring(i,i+5);
 
int speedo= CHK.toInt();  // Conversion from String to Int

if(speedo==0)
{
Serial.println("No Connection");

}
if(speedo>0 && speedo<=500)
{
Serial.println("High Speed");

}
if(speedo>500 && speedo<=1000)
{
Serial.println("Slow Speed");
}
     
    

}

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    ss.print(command); // send the read character to the ss
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(ss.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = ss.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}

 
