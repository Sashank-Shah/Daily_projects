#include <LiquidCrystal.h>
#define BUZZ_LED 6

#define GAS_PIN A1
#define FLAME_PIN A0

int res;


//also incllude that when no fire is detected and gas is detected buzzer will on and display warnin
//menu option to accept two options continuos check or cooking time check

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  
  lcd.begin(16, 2);
  pinMode(FLAME_PIN, INPUT);
  pinMode(GAS_PIN, INPUT);
  pinMode(BUZZ_LED, OUTPUT);

  lcd.setCursor(5, 0);
  lcd.print("DETECTOR");
  lcd.setCursor(5,1);
  lcd.print("STARTED");
  delay(500);
  lcd.clear(); 


}
void sensorRead(int pin) {
  if(digitalRead(pin)==1) {
    res=1;
  }
  else {
    res=0;
  }
  
}
void toneOne() {
  tone(BUZZ_LED, 1000);
  delay(500);
  noTone(BUZZ_LED);
}

void toneTwo() {
  tone(BUZZ_LED, 1000);
  delay(500);
  noTone(BUZZ_LED);
}

void loop() {
  sensorRead(GAS_PIN);
  int value = res;
  sensorRead(FLAME_PIN);
  int val2 = res;

  if(value==1 && val2==1) {
    lcd.setCursor(5, 0);
    lcd.print("STOVE IS ON");
    delay(1000);
    lcd.clear();  
  }
  if(value==1 && val2==0) {
    lcd.setCursor(5, 0);
    lcd.print("GAS LEAKAGE");
    lcd.setCursor(7, 1);
    lcd.print("WARNING");
    toneOne();
    delay(1000);
    lcd.clear(); 
     
  }
  if(val2==1 && value==0) {
    lcd.setCursor(6, 0);
    lcd.print("FIRE");
    lcd.setCursor(6, 1);
    lcd.print("DETECTED");
    toneTwo();
    delay(1000);
    lcd.clear();
  }
  
}
