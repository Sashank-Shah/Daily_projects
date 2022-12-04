/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/

#include <ESP8266WiFi.h>


#define STASSID "POCO X2"
#define STAPSK  "Wifijoinkar"


const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "192.168.107.141";
const uint16_t port = 80;

void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);
  //int temp = 202;
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(5000);
    return;
  }

  // This will send a string to the s erver
  Serial.println("sending data to server");
  if (client.connected()) {
    //client.println("GET /about/?Data="+String(temp)+" HTTP/1.1");
    client.println("GET /stun/1 HTTP/1.1");
    client.println("Host: "+String(host));
    client.println("Content-Type: application/json");
    client.println("Connection: keep-alive");
    client.println();
  }
  //temp = temp+1;
  // wait for data to be available
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(60000);
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  Serial.println("receiving from remote server");
  // not testing 'client.connected()' since we do not need to send data here
  while (client.available()) {
    char ch = static_cast<char>(client.read());
    //Serial.println("Enntered");
    //char ch = client.read();
    String dta = client.readStringUntil('\r');
    Serial.print(dta);
    
  }

  // Close the connection
  Serial.println();
  Serial.println("closing connection");
  client.stop();

  delay(3000); // execute once every 5 minutes, don't flood remote service
}
