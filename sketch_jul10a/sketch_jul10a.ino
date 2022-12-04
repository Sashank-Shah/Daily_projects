//POST the data to the server and see it on a web browser

#include <ESP8266WiFi.h>
//Wifi details
const char* ssid = "POCO X2";
const char* password = "Wifijoinkar";

//Server details
char* host = "www.httpbin.org";
 int port = 80;


/*char* host = "192.168.232.141";
int port = 8000;
*/

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
  WiFiClient client;
  /*String requestData = "temp={\"requestVar\":\"test\"}";*/
  /*String requestData = "requestVar=" + String(lightValue); (for GET payload)*/
  String  data;
  data="Humidity";
  data+="15";
  String vare = "test=" + data;
  if(client.connect(host, port))
 {
  
  Serial.println("[INFO] Server Connected - HTTP GET Started");   
    // Make HTTP GET request
  client.println("POST /post HTTP/1.1");
  // client.println("GET /lightSensorTweet?" + requestData + " HTTP/1.1");
  
  client.println("Host: www.httpbin.org");
  client.println("User-Agent: Arduino/1.0");
  client.println("Connection: close"); 
  client.println("Content-Type:  application/x-www-form-urlencoded");
  client.print("Content-Length: ");
  client.println(vare.length());
  client.println();
  client.println(vare);
  Serial.print("Sent: ");
  Serial.println(vare);
  Serial.println("[INFO] HTTP GET Completed");
 }
 delay(3000);
 while (client.available()) {
    char ch = static_cast<char>(client.read());
    Serial.print(ch);
    
  }
 
 delay(10000);
 

}
