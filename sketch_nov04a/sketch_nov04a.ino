#define S0 D0                             /* Assign Multiplexer pin S0 connect to pin D0 of NodeMCU */
#define S1 D1                             /* Assign Multiplexer pin S1 connect to pin D1 of NodeMCU */
#define S2 D2                             /* Assign Multiplexer pin S2 connect to pin D2 of NodeMCU */
#define S3 D3                             /* Assign Multiplexer pin S3 connect to pin D3 of NodeMCU */
#define SIG A0                            /* Assign SIG pin as Analog output for all 16 channels of Multiplexer to pin A0 of NodeMCU */

int sensor0;                            /* Assign the name "sensor0" as analog output value from Channel C0 */
int sensor1;                            /* Assign the name "sensor1" as analog output value from Channel C1 */
int sensor2;                            /* Assign the name "sensor2" as analog output value from Channel C2 */


void setup() {
  // put your setup code here, to run once:
   pinMode(S0,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin SO */        
   pinMode(S1,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S1 */  
   pinMode(S2,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S2 */ 
   pinMode(S3,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S3 */  
   pinMode(SIG, INPUT);                      /* Define analog signal pin as input or receiver from the Multiplexer pin SIG */  
   Serial.begin(9600);                       /* to display readings in Serial Monitor at 9600 baud rates */
  
}

void loop() {
    digitalWrite(S0,LOW); digitalWrite(S1,LOW); digitalWrite(S2,LOW); digitalWrite(S3,LOW);
    sensor0 = analogRead(SIG);
  
    // Channel 1 (C1 pin - binary output 1,0,0,0)
    digitalWrite(S0,HIGH); digitalWrite(S1,LOW); digitalWrite(S2,LOW); digitalWrite(S3,LOW);
    sensor1 = analogRead(SIG);
  
    // Channel 2 (C2 pin - binary output 0,1,0,0)
    digitalWrite(S0,LOW); digitalWrite(S1,HIGH); digitalWrite(S2,LOW); digitalWrite(S3,LOW);
    sensor2 = analogRead(SIG);
    
    Serial.print("Sensor 0 : ");Serial.println(sensor0);          /* state value for sensor 0 */
    Serial.print("Sensor 1 : ");Serial.println(sensor1);          /* state value for sensor 1 */
    Serial.print("Sensor 2 : ");Serial.println(sensor2);          /* state value for sensor 2 */

    delay(1000);
}
