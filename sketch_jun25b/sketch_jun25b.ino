//Coded and compiled by SASHANK SHAH
//Calculator program


#include <Keypad.h>

const byte ROWS = 4; // Four rows of the keypad
const byte COLS = 4; // Three columns of the keypad

// Define the Keymap
char keys[ROWS][COLS] = {
{'7','8','9','/'},
{'4','5','6','*'},
{'1','2','3','-'},
{'c','0','=','+'}
};

// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins 0,1,2,3 respectively.
byte rowPins[ROWS] = { 2, 3, 4, 5 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins 4,5,67 respectively. 
byte colPins[COLS] = { 6, 7, 8, 9 };  

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //  Create the Keypad

long Num1=0,Num2=0,Number=0;
char key,action;
boolean result = false;

void setup() {
  Serial.begin(9600);

}
void CalculateResult()
{
if (action=='+')      // if + sign is pressed
Number = Num1+Num2;   // add both numbers

if (action=='-')      // if - sign is pressed
Number = Num1-Num2;   // subtract both numbers

if (action=='*')      // if * sign is pressed
Number = Num1*Num2;   //multiply both numbers

if (action=='/')      // if / sign is pressed
Number = Num1/Num2;   // divide both numbers
}
void DisplayResult()
{
if (result==true)        //Display the result
{
Serial.println(Number);       // print the answer on the screen
}
result=false;
Number=Num1=Num2=0;
}
void DetectButtons()
{
 if (key=='c')                      //If cancel Button is pressed
 {
  Serial.print(" "); // print a comment 
  Number=Num1=Num2=0; 
  result=false;
 }

 if (key == '1')                     //If Button 1 is pressed
 {
  Serial.print (key); 
  if (Number==0)
   Number=1;
  else
   Number = (Number*10) + 1;         //Pressed twice
 }

 if (key == '4')                     //If Button 4 is pressed
 {
  Serial.print (key); 
  if (Number==0)
   Number=4;
  else
   Number = (Number*10) + 4;         //Pressed twice
 }

 if (key == '7')                     //If Button 7 is pressed
 {
  Serial.print (key);
  if (Number==0)
   Number=7;
  else
   Number = (Number*10) + 7;         //Pressed twice
 } 

 if (key == '0')                     //If Button 0 is pressed
 {
  Serial.print (key); 
  if (Number==0)
   Number=0;
  else
   Number = (Number*10) + 0;         //Pressed twice
 }

 if (key == '2')                     //Button 2 is Pressed
 {
  Serial.print (key); 
  if (Number==0)
   Number=2;
  else
   Number = (Number*10) + 2;         //Pressed twice
 }

 if (key == '5')                     //Button 5 is Pressed
 {
  Serial.print (key); 
  if (Number==0)
   Number=5;
  else
   Number = (Number*10) + 5;         //Pressed twice
 }

 if (key == '8')                     //Button 8 is Pressed
 {
  Serial.print (key); 
  if (Number==0)
   Number=8;
  else
   Number = (Number*10) + 8;         //Pressed twice
 } 

 if (key == '=')                     //Button = is Pressed
 {
 Serial.print (key);
 Num2=Number;
 Number=0;
 result = true;
 }

 if (key == '3')                     //Button 3 is Pressed
 {
  Serial.print (key); 
  if (Number==0)
   Number=3;
  else
   Number = (Number*10) + 3;         //Pressed twice
 }

 if (key == '6')                     //Button 6 is Pressed
 { 
  Serial.print (key); 
  if (Number==0)
   Number=6;
  else
   Number = (Number*10) + 6;         //Pressed twice
 }

 if (key == '9')                     //Button 09 is Pressed
 {
  Serial.print (key);
  if (Number==0)
   Number=9;
  else
   Number = (Number*10) + 9;         //Pressed twice
 }

 if (key == '/' || key == '*' || key == '-' || key == '+')  //Detecting Buttons on Column 4
 {
  Num1 = Number; 
  Number =0;
  if (key == '+')
  { 
   Serial.print (key); 
   action = '+';
  }
  if (key == '-')
  {
   Serial.print (key); 
   action = '-'; 
  } 
  if (key == '*')
  {
   Serial.print (key); 
   action = '*';
  }
  if (key == '/')
  {
   Serial.print (key); 
   action = '/';
  }

  delay(100);
 }
}

void loop() {
  key = kpd.getKey();  //storing pressed key value in a char

  if (key!=NO_KEY) {
  DetectButtons();     // call function
  }
  if (result==true) {
  CalculateResult();   // call function
  DisplayResult();
  }

}
