#include <Servo.h>

#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);


Servo myservo;
char indexPage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <!---------------------------Button Css starts here-------------------------->
<style>
body{
  background-color: lightblue;
}
.button {
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
  border: 5px outset red;

}

.button1,
.button2 {background-color: red;} /* Green */


.button1:hover,
.button2:hover {
  background-color: yellowgreen;
  color: white;
}

</style>
<!---------------------------Button Css ends here-------------------------->
</head>
<body>
<center>
<h1>Use the buttons</h1>
<div>
  <button class="button button1" onclick="window.location='http://'+location.hostname+'/move/left'">Left</button>
  <button class="button button2" onclick="window.location='http://'+location.hostname+'/move/Rigth'">Right</button>
</div>

</center>
</body>
</html>
)=====";



void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not Found");
}
void moveRight(void)
{
  int pos;
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void moveLeft(void)
{
  int pos;
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
   
}


void setup() {
  // put your setup code here, to run once:
  myservo.attach(D0);
  Serial.begin(115200);
  WiFi.softAP("YourHomeServer", "");
  Serial.println("SoftAp: ");
  Serial.println(WiFi.softAPIP());

  if(MDNS.begin("esp"))
  {
    Serial.println("MDNS response started");
  }
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(200, "text/html", indexPage);
  });
  server.on("/move/left", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    
    request->send(200, "text/html", indexPage);
    moveLeft();
  });
  server.on("/move/Rigth", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(200, "text/html", indexPage);
    moveRight();
  });
  
  server.onNotFound(notFound);
  server.begin();
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
