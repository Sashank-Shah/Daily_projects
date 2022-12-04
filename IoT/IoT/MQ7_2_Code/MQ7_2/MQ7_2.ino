int gas_sensor = A0; //Sensor pin 
float m = -0.6527; //Slope 
float b = 1.30; //Y-Intercept 
float R0 = 0.71; //Sensor Resistance in fresh air from previous code
 
void setup() {
  Serial.begin(9600); //Baud rate 
 
  pinMode(gas_sensor, INPUT); //Set gas sensor as input 
}
 
void loop() {  
 
  float sensor_volt; //Define variable for sensor voltage 
  float RS_gas; //Define variable for sensor resistance  
  float ratio; //Define variable for ratio
  int sensorValue = analogRead(gas_sensor); //Read analog values of sensor  

  sensor_volt = sensorValue*(4.0/1023.0); //Convert analog values to voltage 
  RS_gas = ((4.0*10.0)/sensor_volt)-10.0; //Get value of RS in a gas
  ratio = RS_gas/R0;  // Get ratio RS_gas/RS_air
  double ppm_log = (log10(ratio)-b)/m; //Get ppm value in linear scale according to the the ratio value  
  double ppm = pow(10, ppm_log); //Convert ppm value to log scale 
  Serial.print("PPM = ");
  Serial.println(ppm);
  delay(2000);
}
